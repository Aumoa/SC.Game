#pragma unmanaged

using namespace SC;
using namespace SC::Game;

gcroot<Scene^> GameLogic::mCurrentScene;
gcroot<Scene^> GameLogic::mRemovedScenes[2];

CDeviceContext GameLogic::mDeviceContext;

GeometryBuffer GameLogic::mGeometryBuffer;
HDRBuffer GameLogic::mHDRBuffer;

D3D12_RECT GameLogic::mScissorRect;
D3D12_VIEWPORT GameLogic::mViewport;

void GameLogic::Initialize()
{
	App::Disposing.push_front( OnDisposing );
	App::Resizing.push_back( OnResizing );

	mDeviceContext = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );

	mGeometryBuffer = GeometryBuffer();
	mHDRBuffer = HDRBuffer();
}

#pragma managed
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

	Input::mScrollDelta = System::Drawing::PointF( 0, 0 );
}

void GameLogic::Render()
{
	mDeviceContext.Reset( App::mFrameIndex, nullptr );

	// 카메라 컬렉션이 존재할 경우에만 3D 렌더링을 수행합니다.
	if ( mCurrentScene && mCurrentScene->mSceneCameras->Count )
	{
		GeometryWriting();
	}

	Present();
}
#pragma unmanaged

void GameLogic::OnDisposing()
{
	mDeviceContext.Dispose();

	mGeometryBuffer.Dispose();
	mHDRBuffer.Dispose();
}

void GameLogic::OnResizing( int width, int height )
{
	mGeometryBuffer.ResizeBuffers( width, height );

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
void GameLogic::GeometryWriting()
{
	auto& dc = mDeviceContext;

	dc.SetGraphicsRootSignature( ShaderBuilder::pRootSignature3D.Get() );
	dc.SetPipelineState( ShaderBuilder::pPipelineStateColor.Get() );

	for each ( auto cam in mCurrentScene->mSceneCameras )
	{
		mGeometryBuffer.OMSetRenderTargets( dc );
		dc.SetGraphicsRootConstantBufferView( ( UINT )Slot_3D_Camera, cam->mConstantBuffer->GetGPUVirtualAddress() );
		
		for each ( auto meshRenderer in mCurrentScene->mSceneMeshRenderers )
		{
			meshRenderer->Render( dc );
		}

		mGeometryBuffer.EndDraw( dc );
	}
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

		mDeviceContext.SetGraphicsRootShaderResource( Slot_PP_HDRBuffer, mGeometryBuffer.ppShaderResourceViews[0] );

		mDeviceContext.IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
		mDeviceContext.DrawInstanced( 4, 1 );
	}

	mDeviceContext.Close();

	Graphics::mCoreQueue->Execute( mDeviceContext );
}
#pragma unmanaged