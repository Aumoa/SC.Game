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
	// â�� ȭ�鿡 ǥ���մϴ�.
	ShowWindow( hWnd, SW_SHOW );

	// ���� �� �޽��� ������ �����մϴ�.
	MSG msg{ };
	while ( true )
	{
		// �޽��� ť�� �޽����� ���� ��� �޽����� ���� ó���� �����մϴ�.
		// �޽��� ó���� �������� �ʵ��� �׻� �켱������ ó���մϴ�.
		if ( PeekMessageW( &msg, nullptr, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
			{
				break;
			}

			TranslateMessage( &msg );
			DispatchMessageW( &msg );
		}

		// �޽��� ť�� �޽����� ���� ��� ���� ���� ó���մϴ�.
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
	// ���� �������� �������� �Ϸ���� �ʾҴٸ� ����մϴ�.
	if ( mFence->GetCompletedValue() < mLastPending[mFrameIndex] )
	{
		HR( mFence->SetEventOnCompletion( mLastPending[mFrameIndex], mFenceEvent ) );
		WaitForSingleObject( mFenceEvent, INFINITE );
	}

	// ���� �� ������ �����ϱ� �� ������ �÷��Ϳ��� �����͸� �����մϴ�.
	GC::Collect();

	Update();
	if ( !mDisablePresent )
	{
		HeapCommit();
		Render();

		// �۷ι� GC ��⿭�� Ǫ���մϴ�.
		mHeapCommitDCAndGC.GCFlush( mFence.Get(), mLastPending[mFrameIndex] );
	}
}

#pragma managed
void App::OnSize( int width, int height )
{
	if ( width * height != 0 )
	{
		// ũ�� ���� ��û�� ������ ��, �켱 ������ ��ɰ� ����ȭ�մϴ�.
		if ( mFence->GetCompletedValue() < mFenceValue )
		{
			HR( mFence->SetEventOnCompletion( mFenceValue, mFenceEvent ) );
			WaitForSingleObject( mFenceEvent, INFINITE );
		}

		// ũ�� ��û �̺�Ʈ�� �����ϴ�.
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
		// ũ�Ⱑ 0�� ��� �ּ�ȭ�� ����, �������� �������� �ʽ��ϴ�.
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
		throw exception( "SC.Game.Details.App.CreateWindow(): Windows â Ŭ������ �ʱ�ȭ�ϴµ� �����Ͽ����ϴ�." );
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
		throw exception( "SC.Game.Details.App.CreateWindow(): Windows â�� �����ϴµ� �����Ͽ����ϴ�." );
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

	// �ĸ� ���۸� ����մϴ�.
	Graphics::mSwapChain->Present( mVSync );

	// ��� ��ȣ�� �����ϴ�.
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