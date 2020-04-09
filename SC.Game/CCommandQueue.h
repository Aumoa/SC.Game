#pragma once

namespace SC::Game
{
	class CDeviceContext;

	class CCommandQueue
	{
	public:
		CCommandQueue( D3D12_COMMAND_LIST_TYPE type, D3D12_COMMAND_QUEUE_PRIORITY priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL );

		void Execute( CDeviceContext& deviceContext );
		void Execute( int numContexts, CDeviceContext** ppDeviceContexts );
		UINT64 Signal();
		void Signal( ID3D12Fence* pFence, UINT64 fenceValue );

		ComPtr<ID3D12CommandQueue> pCommandQueue;
		ComPtr<ID3D12Fence> pFence;
		UINT64 mFenceValue = 0;
	};
}