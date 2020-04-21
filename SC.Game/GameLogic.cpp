#pragma unmanaged

using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Collections::Generic;

using namespace std;

gcroot<Scene^> GameLogic::mCurrentScene;
gcroot<Scene^> GameLogic::mRemovedScenes[2];

CDeviceContext GameLogic::mDeviceContext;
CDeviceContext GameLogic::mDeviceContextMeshSkinning;
CDeviceContext GameLogic::mDeviceContextGeometryWriting;
CDeviceContext GameLogic::mDeviceContextShadowCast[8];
CDeviceContext GameLogic::mDeviceContextHDR;
CDeviceContext GameLogic::mDeviceContextHDRCompute;

GeometryBuffer GameLogic::mGeometryBuffer;
HDRBuffer GameLogic::mHDRBuffer;
HDRComputedBuffer GameLogic::mHDRComputedBuffer;

D3D12_RECT GameLogic::mScissorRect;
D3D12_VIEWPORT GameLogic::mViewport;

gcroot<Mesh^> GameLogic::mMesh;

#pragma managed

namespace
{
	ref class ShadowRenderLambda
	{
	public:
		Light^ mLight;
		int mID;

		void Task()
		{
			GameLogic::ShadowRender( mLight, mID );
		}
	};
}

void GameLogic::Initialize()
{
	App::Disposing.push_front( OnDisposing );
	App::Resizing.push_back( OnResizing );

	mDeviceContext = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextMeshSkinning = CDeviceContext( D3D12_COMMAND_LIST_TYPE_COMPUTE );
	mDeviceContextGeometryWriting = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[0] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[1] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[2] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[3] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[4] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[5] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[6] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextShadowCast[7] = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextHDR = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDeviceContextHDRCompute = CDeviceContext( D3D12_COMMAND_LIST_TYPE_COMPUTE );

	mGeometryBuffer = GeometryBuffer();
	mHDRBuffer = HDRBuffer();

	mMesh = Mesh::CreateCube( "skybox_mesh" );
}

void GameLogic::Update()
{
	if ( mRemovedScenes[App::mFrameIndex] )
	{
		mRemovedScenes[App::mFrameIndex] = nullptr;
	}

	if ( auto resolve = ( Scene^ )mCurrentScene; SceneManager::mCurrentScene && resolve != SceneManager::mCurrentScene )
	{
		mRemovedScenes[App::mFrameIndex].swap( mCurrentScene );

		mCurrentScene = SceneManager::mCurrentScene;
		SceneManager::mCurrentScene = nullptr;
	}

	Input::Update();

	if ( mCurrentScene )
	{
		mCurrentScene->Update();
	}

	Input::LateUpdate();
}

void GameLogic::Render()
{
	auto& directQueue = Graphics::mCoreQueue;
	auto& computeQueue = Graphics::mComputeQueue;

	mDeviceContext.Reset( App::mFrameIndex, nullptr );

	// 카메라 컬렉션이 존재할 경우에만 3D 렌더링을 수행합니다.
	if ( mCurrentScene && mCurrentScene->mSceneCameras->Count )
	{
		MeshSkinning();

		auto threadCount = ShadowCast();
		GeometryWriting();

		Task::WaitAll( threadCount );
		HDRRender();
		HDRCompute();

		computeQueue->Execute( mDeviceContextMeshSkinning );
		auto signal = computeQueue->Signal();

		HR( directQueue->pCommandQueue->Wait( computeQueue->pFence.Get(), signal ) );
		directQueue->Execute( mDeviceContextGeometryWriting );
		directQueue->Execute( threadCount->Length, mDeviceContextShadowCast );
		directQueue->Execute( mDeviceContextHDR );
		signal = directQueue->Signal();

		HR( computeQueue->pCommandQueue->Wait( directQueue->pFence.Get(), signal ) );
		computeQueue->Execute( mDeviceContextHDRCompute );
		signal = computeQueue->Signal();

		HR( directQueue->pCommandQueue->Wait( computeQueue->pFence.Get(), signal ) );
	}

	Present();
}
#pragma unmanaged

void GameLogic::OnDisposing()
{
	mDeviceContext.Dispose();
	mDeviceContextGeometryWriting.Dispose();
	mDeviceContextShadowCast[0].Dispose();
	mDeviceContextShadowCast[1].Dispose();
	mDeviceContextShadowCast[2].Dispose();
	mDeviceContextShadowCast[3].Dispose();
	mDeviceContextShadowCast[4].Dispose();
	mDeviceContextShadowCast[5].Dispose();
	mDeviceContextShadowCast[6].Dispose();
	mDeviceContextShadowCast[7].Dispose();
	mDeviceContextHDR.Dispose();
	mDeviceContextHDRCompute.Dispose();

	mGeometryBuffer.Dispose();
	mHDRBuffer.Dispose();
}

void GameLogic::OnResizing( int width, int height )
{
	mGeometryBuffer.ResizeBuffers( width, height );
	mHDRBuffer.ResizeBuffers( width, height );
	mHDRComputedBuffer.ResizeBuffers( width, height );

	mScissorRect.left = 0;
	mScissorRect.top = 0;
	mScissorRect.right = width;
	mScissorRect.bottom = height;

	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mViewport.Width = ( float )width;
	mViewport.Height = ( float )height;
	mViewport.MinDepth = 0;
	mViewport.MaxDepth = 1.0f;
}

#pragma managed
void GameLogic::MeshSkinning()
{
	auto& dc = mDeviceContextMeshSkinning;

	dc.Reset( App::mFrameIndex, ShaderBuilder::pPipelineState_Skinning.Get() );
	dc.SetComputeRootSignature( ShaderBuilder::pRootSignature_Skinning.Get() );

	for each ( auto pair in mCurrentScene->mSkinnedMeshRendererQueue->mSkinnedPair )
	{
		pair.pAnimator->SetInput( dc );
		for each ( auto skin in pair.SkinnedMeshRenderers )
		{
			skin->Skinning( dc );
		}
	}

	dc.Close();
}

void GameLogic::GeometryWriting()
{
	auto& dc = mDeviceContextGeometryWriting;

	dc.Reset( App::mFrameIndex );
	dc.SetGraphicsRootSignature( ShaderBuilder::pRootSignature3D.Get() );

	for each ( auto cam in mCurrentScene->mSceneCameras )
	{
		mGeometryBuffer.OMSetRenderTargets( dc );
		dc.SetGraphicsRootConstantBufferView( ( UINT )Slot_3D_Camera, cam->mConstantBuffer->GetGPUVirtualAddress() );

		dc.SetPipelineState( ShaderBuilder::pPipelineStateSkybox.Get() );
		if ( cam->mSkyboxTexture )
		{
			dc.SetGraphicsRootShaderResource( Slot_3D_Textures, *cam->mSkyboxTexture->mShaderResourceView );
			mMesh->DrawIndexed( dc );
		}
		
		dc.SetPipelineState( ShaderBuilder::pPipelineStateColor.Get() );
		for each ( auto meshRenderer in mCurrentScene->mSceneMeshRenderers )
		{
			meshRenderer->Render( dc );
		}
		for each ( auto pair in mCurrentScene->mSkinnedMeshRendererQueue->mSkinnedPair )
		{
			for each ( auto skin in pair.SkinnedMeshRenderers )
			{
				skin->Render( dc );
			}
		}

		mGeometryBuffer.EndDraw( dc );
	}

	dc.Close();
}

cli::array<Task^>^ GameLogic::ShadowCast()
{
	int threadIdx = 0;
	int threadCount = 0;

	auto vector = gcnew List<Task^>();

	for each ( auto light in mCurrentScene->mSceneLights )
	{
		int idx = threadIdx++;
		threadCount = max( threadCount, threadIdx );
		if ( threadIdx >= 8 ) threadIdx = 0;

		auto lambda = gcnew ShadowRenderLambda();
		lambda->mLight = light;
		lambda->mID = idx;
		
		vector->Add( Task::Run( gcnew Action( lambda, &ShadowRenderLambda::Task ) ) );
	}

	auto arr = gcnew cli::array<Task^>( vector->Count );
	vector->CopyTo( arr, 0 );

	return arr;
}

void GameLogic::HDRRender()
{
	auto& dc = mDeviceContextHDR;

	dc.Reset( App::mFrameIndex, ShaderBuilder::pPipelineStateLighting.Get() );
	dc.SetGraphicsRootSignature( ShaderBuilder::pRootSignatureHDR.Get() );
	dc.IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	mHDRBuffer.OMSetRenderTargets( dc );

	auto firstCamera = mCurrentScene->mSceneCameras[0];
	dc.SetGraphicsRootConstantBufferView( ( UINT )Slot_HDR_Camera, firstCamera->mConstantBuffer->GetGPUVirtualAddress() );
	dc.SetGraphicsRootShaderResource( ( UINT )Slot_HDR_GeometryBuffer, 4, mGeometryBuffer.ppShaderResourceViews );
	dc.SetGraphicsRootShaderResourceView( ( UINT )Slot_HDR_Reflection, Material::mReflectionBuffer->GetGPUVirtualAddress() );

	// 라이팅을 진행합니다.
	for each ( auto light in mCurrentScene->mSceneLights )
	{
		dc.SetGraphicsRootConstantBufferView( ( UINT )Slot_HDR_LightConstant, light->mConstantBuffer->GetGPUVirtualAddress() );
		if ( light->IsShadowCast )
		{
			dc.SetGraphicsRootShaderResource( ( UINT )Slot_HDR_LightShadow, *light->mShaderResourceView );
		}
		dc.DrawInstanced( 4, 1 );
	}

	// 색상 덮어쓰기를 진행합니다.
	dc.SetPipelineState( ShaderBuilder::pPipelineStateHDRColor.Get() );
	dc.DrawInstanced( 4, 1 );

	mHDRBuffer.EndDraw( dc );

	dc.Close();
}

void GameLogic::HDRCompute()
{
	auto& dc = mDeviceContextHDRCompute;

	dc.Reset( App::mFrameIndex, ShaderBuilder::pPipelineStateSamplingCompute.Get() );
	dc.SetComputeRootSignature( ShaderBuilder::pRootSignatureHDRCompute.Get() );
	mHDRComputedBuffer.SetComputeRootTimestamp( dc, Time::DeltaTime );
	mHDRBuffer.SetComputeRootShaderResources( dc );
	mHDRComputedBuffer.Compute( dc, 0 );

	dc.SetPipelineState( ShaderBuilder::pPipelineStateLumCompressCompute.Get() );
	mHDRComputedBuffer.Compute( dc, 1 );

	dc.SetPipelineState( ShaderBuilder::pPipelineStateAverageLumCompute.Get() );
	mHDRComputedBuffer.Compute( dc, 2 );

	dc.Close();
}

void GameLogic::Present()
{
	auto index = Graphics::mSwapChain->Index();
	auto pResource = Graphics::mSwapChain->ppBackBuffers[index].Get();
	auto rtv = Graphics::mSwapChain->RTVHandle[index];

	mDeviceContext.TransitionBarrier( pResource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, 0 );

	mDeviceContext.OMSetRenderTargets( 1, &rtv, FALSE, nullptr );
	mDeviceContext.ClearRenderTargetView( rtv, { } );

	mDeviceContext.RSSetScissorRects( 1, &mScissorRect );
	mDeviceContext.RSSetViewports( 1, &mViewport );

	if ( mCurrentScene && mCurrentScene->mSceneCameras->Count )
	{
		mDeviceContext.SetGraphicsRootSignature( ShaderBuilder::pRootSignaturePP.Get() );
		mDeviceContext.SetPipelineState( ShaderBuilder::pPipelineStateToneMapping.Get() );

		mDeviceContext.SetGraphicsRootShaderResource( Slot_PP_HDRBuffer, mHDRBuffer.ppShaderResourceViews[0] );
		mDeviceContext.SetGraphicsRootConstantBufferView( Slot_PP_HDRConstants, mHDRComputedBuffer.pHDRConstants->GetGPUVirtualAddress() );

		mDeviceContext.IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
		mDeviceContext.DrawInstanced( 4, 1 );
	}

	mDeviceContext.Close();

	Graphics::mCoreQueue->Execute( mDeviceContext );
}

void GameLogic::ShadowRender( Light^ light, int threadIdx )
{
	auto& dc = mDeviceContextShadowCast[threadIdx];

	dc.Reset( App::mFrameIndex, ShaderBuilder::pPipelineStateShadowCast.Get() );
	dc.SetGraphicsRootSignature( ShaderBuilder::pRootSignature3D.Get() );

	if ( light->IsShadowCast )
	{
		light->BeginDraw( dc );
		dc.SetGraphicsRootConstantBufferView( ( UINT )Slot_3D_Light, light->mConstantBuffer->GetGPUVirtualAddress() );

		for each ( auto meshRenderer in mCurrentScene->mSceneMeshRenderers )
		{
			meshRenderer->Render( dc );
		}
		for each ( auto pair in mCurrentScene->mSkinnedMeshRendererQueue->mSkinnedPair )
		{
			for each ( auto skin in pair.SkinnedMeshRenderers )
			{
				skin->Render( dc );
			}
		}

		light->EndDraw( dc );
	}

	dc.Close();
}

#pragma unmanaged