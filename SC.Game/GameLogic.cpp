#pragma unmanaged

using namespace SC;
using namespace SC::Game;

CDeviceContext GameLogic::mDeviceContext;
gcroot<Scene^> GameLogic::mCurrentScene;
gcroot<Scene^> GameLogic::mRemovedScenes[2];

void GameLogic::Initialize()
{
	App::Disposing.push_front( OnDisposing );

	mDeviceContext = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );
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
#pragma unmanaged

void GameLogic::Render()
{
	mDeviceContext.Reset( App::mFrameIndex, nullptr );

	Present();
}

void GameLogic::OnDisposing()
{
	mDeviceContext.Dispose();
}

void GameLogic::Present()
{
	auto index = Graphics::mSwapChain->Index();
	auto pResource = Graphics::mSwapChain->ppBackBuffers[index].Get();
	auto rtv = Graphics::mSwapChain->RTVHandle[index];

	mDeviceContext.TransitionBarrier( pResource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, 0 );
	mDeviceContext.ClearRenderTargetView( rtv, { } );

	// TODO: 여기에 Present 렌더링 목록을 작성합니다.

	mDeviceContext.Close();

	Graphics::mCoreQueue->Execute( mDeviceContext );
}