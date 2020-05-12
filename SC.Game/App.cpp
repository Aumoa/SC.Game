using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

HWND App::hWnd;
Event<DisposingDelegate> App::Disposing;
Event<ResizingDelegate> App::Resizing;
bool App::mDisposed;

wstring App::mAppName;
int App::mPhysicsHz;
bool App::mVSync;
bool App::mDisablePresent;
bool App::mActivated;

int App::mFrameIndex;
ComPtr<ID3D12Fence> App::mFence;
UINT64 App::mFenceValue;
UINT64 App::mLastPending[2];
HANDLE App::mFenceEvent;

CDeviceContext App::mHeapCommitDCAndGC;

#pragma managed
void App::Initialize()
{
	Disposing.push_front( OnDisposing );

	CreateWindow1();

	Graphics::Initialize();
	Physics::Initialize();
	ShaderBuilder::Initialize();
	GC::Initialize();
	HeapAllocator::Initialize();
	Material::Initialize();
	GameLogic::Initialize();
	UISystem::Initialize();

	CreateFence();
	mHeapCommitDCAndGC = CDeviceContext( D3D12_COMMAND_LIST_TYPE_DIRECT );

#if defined( _DEBUG )
	mHeapCommitDCAndGC.Reset( 0 );
	mHeapCommitDCAndGC.Close();
	debug_name( App::mHeapCommitDCAndGC.mCommandList );
#endif
}
#pragma unmanaged

void App::DisposeAll()
{
	for ( auto i : Disposing )
	{
		i();
	}
}

void App::CoreLoop()
{
	// 창을 화면에 표시합니다.
	ShowWindow( hWnd, SW_SHOW );

	// 앱의 주 메시지 루프를 시작합니다.
	MSG msg{ };
	while ( true )
	{
		// 메시지 큐에 메시지가 있을 경우 메시지에 대한 처리를 수행합니다.
		// 메시지 처리가 지연되지 않도록 항상 우선적으로 처리합니다.
		if ( PeekMessageW( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
			{
				break;
			}

			TranslateMessage( &msg );
			DispatchMessageW( &msg );
		}

		// 메시지 큐에 메시지가 없을 경우 앱의 논리를 처리합니다.
		else
		{
			OnIdle();
		}
	}

	mDisposed = true;
}

void App::GCAdd( ComPtr<IUnknown> pUnknown )
{
	mHeapCommitDCAndGC.GCAdd( move( pUnknown ) );
}

void App::OnDisposing()
{
	if ( mFence && mFence->GetCompletedValue() < mFenceValue )
	{
		HR( mFence->SetEventOnCompletion( mFenceValue, mFenceEvent ) );
		WaitForSingleObject( mFenceEvent, INFINITE );
	}

	if ( mFenceEvent )
	{
		CloseHandle( mFenceEvent );
		mFenceEvent = nullptr;
	}

	mFence.Reset();
}

void App::OnIdle()
{
	// 이전 프레임의 렌더링이 완료되지 않았다면 대기합니다.
	if ( mFence->GetCompletedValue() < mLastPending[mFrameIndex] )
	{
		HR( mFence->SetEventOnCompletion( mLastPending[mFrameIndex], mFenceEvent ) );
		WaitForSingleObject( mFenceEvent, INFINITE );
	}

	// 다음 논리 갱신을 수행하기 전 가비지 컬렉터에서 데이터를 수집합니다.
	GC::Collect();

	Update();
	if ( !mDisablePresent )
	{
		HeapCommit();
		Render();

		// 글로벌 GC 대기열을 푸쉬합니다.
		mHeapCommitDCAndGC.GCFlush( mFence.Get(), mLastPending[mFrameIndex] );
	}
}

#pragma managed
void App::OnSize( int width, int height )
{
	if ( width * height != 0 )
	{
		// 크기 변경 요청을 보내기 전, 우선 마지막 명령과 동기화합니다.
		if ( mFence->GetCompletedValue() < mFenceValue )
		{
			HR( mFence->SetEventOnCompletion( mFenceValue, mFenceEvent ) );
			WaitForSingleObject( mFenceEvent, INFINITE );
		}

		// 크기 요청 이벤트를 보냅니다.
		for ( auto i : Resizing )
		{
			i( width, height );
		}

		Application::mWidth = width;
		Application::mHeight = height;

		mDisablePresent = false;
	}
	else
	{
		// 크기가 0일 경우 최소화된 경우로, 렌더링을 수행하지 않습니다.
		mDisablePresent = true;
	}
}
#pragma unmanaged

void App::CreateWindow1()
{
	WNDCLASSEXW wcex{ };
	wcex.cbSize = sizeof( wcex );
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"SC.Game.Details.App.CoreWindow";
	wcex.hInstance = GetModuleHandleW( nullptr );

	if ( RegisterClassExW( &wcex ) == 0 )
	{
		throw exception( "SC.Game.Details.App.CreateWindow(): Windows 창 클래스를 초기화하는데 실패하였습니다." );
	}

	hWnd = CreateWindowExW(
		NULL,
		wcex.lpszClassName,
		mAppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		nullptr,
		wcex.hInstance,
		nullptr
	);
	if ( !hWnd )
	{
		throw exception( "SC.Game.Details.App.CreateWindow(): Windows 창을 생성하는데 실패하였습니다." );
	}
}

void App::CreateFence()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	HR( pDevice->CreateFence( 0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS( &mFence ) ) );
	mLastPending[0] = 0;
	mLastPending[1] = 0;
	mFenceValue = 0;

	mFenceEvent = CreateEventExW( nullptr, nullptr, 0, GENERIC_ALL );
}

void App::Update()
{
	mFrameIndex = Graphics::mSwapChain->Index();

	GameLogic::Update();
	UISystem::Update( mFrameIndex );
}

void App::HeapCommit()
{
	mHeapCommitDCAndGC.Reset( mFrameIndex );
	HeapAllocator::Commit( mFrameIndex, mHeapCommitDCAndGC );
	mHeapCommitDCAndGC.Close();

	Graphics::mHighPriorityQueue->Execute( mHeapCommitDCAndGC );
	auto fenceValue = Graphics::mHighPriorityQueue->Signal();
	Graphics::mCoreQueue->pCommandQueue->Wait( Graphics::mHighPriorityQueue->pFence.Get(), fenceValue );
}

void App::Render()
{
	GameLogic::Render();
	UISystem::Render( mFrameIndex );

	// 후면 버퍼를 출력합니다.
	Graphics::mSwapChain->Present( mVSync );

	// 명령 신호를 보냅니다.
	HR( Graphics::mCoreQueue->pCommandQueue->Signal( mFence.Get(), ++mFenceValue ) );
	mLastPending[mFrameIndex] = mFenceValue;
}

#pragma managed
LRESULT CALLBACK App::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_SIZE:
		OnSize( ( int )LOWORD( lParam ), ( int )HIWORD( lParam ) );
		break;
	case WM_MOUSEWHEEL:
		Input::mScrollDelta.Y += ( float )( short )HIWORD( wParam ) / ( float )WHEEL_DELTA;
		break;
	case WM_ACTIVATEAPP:
		Application::mApp->OnActive( ( bool )wParam );
		mActivated = ( bool )wParam;
		break;
	}

	return DefWindowProcW( hWnd, uMsg, wParam, lParam );
}