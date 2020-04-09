using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

CCommandQueue::CCommandQueue( D3D12_COMMAND_LIST_TYPE type, D3D12_COMMAND_QUEUE_PRIORITY priority )
{
	D3D12_COMMAND_QUEUE_DESC desc{ };
	desc.Type = type;
	desc.Priority = priority;

	HR( Graphics::mDevice->pDevice->CreateCommandQueue( &desc, IID_PPV_ARGS( &pCommandQueue ) ) );
	HR( Graphics::mDevice->pDevice->CreateFence( 0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS( &pFence ) ) );
}

void CCommandQueue::Execute( CDeviceContext& deviceContext )
{
	ID3D12CommandList* ppCommandLists[]{ deviceContext.mCommandList.Get() };

	pCommandQueue->ExecuteCommandLists( 1, ppCommandLists );
}

void CCommandQueue::Execute( int numContexts, CDeviceContext** ppDeviceContexts )
{
	vector<ID3D12CommandList*> ppCommandLists( numContexts );
	for ( int i = 0; i < numContexts; ++i )
	{
		ppCommandLists[i] = ppDeviceContexts[i]->mCommandList.Get();
	}

	pCommandQueue->ExecuteCommandLists( ( UINT )numContexts, ppCommandLists.data() );
}

UINT64 CCommandQueue::Signal()
{
	UINT64 value = InterlockedIncrement64( ( volatile LONG64* )&mFenceValue );
	Signal( pFence.Get(), value );
	return value;
}

void CCommandQueue::Signal( ID3D12Fence* pFence, UINT64 fenceValue )
{
	HR( pCommandQueue->Signal( pFence, fenceValue ) );
}