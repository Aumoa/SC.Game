#pragma unmanaged

using namespace SC;
using namespace SC::Game;

using namespace std;

unique_ptr<IntegratedFactory> Graphics::mFactory;
unique_ptr<CDevice> Graphics::mDevice;
unique_ptr<CCommandQueue> Graphics::mCoreQueue;
unique_ptr<CCommandQueue> Graphics::mHighPriorityQueue;
unique_ptr<CCommandQueue> Graphics::mUIQueue;
unique_ptr<CSwapChain> Graphics::mSwapChain;

void Graphics::Initialize()
{
	App::Disposing.push_front( OnDisposing );
	App::Resizing.push_back( OnResizing );

	mFactory = make_unique<IntegratedFactory>();
	auto pAdapter = mFactory->SearchHardwareAdapter();
	mDevice = make_unique<CDevice>( pAdapter.Get() );
	mCoreQueue = make_unique<CCommandQueue>( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mHighPriorityQueue = make_unique<CCommandQueue>( D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_PRIORITY_HIGH );
	mUIQueue = make_unique<CCommandQueue>( D3D12_COMMAND_LIST_TYPE_DIRECT );
	mDevice->InitializeInterop( mUIQueue.get() );
	mSwapChain = make_unique<CSwapChain>();
}

void Graphics::OnDisposing()
{
	mSwapChain.reset();
	mCoreQueue.reset();
	mDevice.reset();
	mFactory.reset();
}

void Graphics::OnResizing( int width, int height )
{
	mSwapChain->ResizeBuffers( width, height );
}