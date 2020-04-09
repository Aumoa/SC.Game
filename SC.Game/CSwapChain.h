#pragma once

namespace SC::Game
{
	class CSwapChain
	{
		ComPtr<ID3D12DescriptorHeap> mRTV;
		int mRTVStride;

	public:
		CSwapChain();

		void ResizeBuffers( int width, int height );
		void Present( bool vSync = false );
		int Index();

		static constexpr const int BufferCount = 2;
		ComPtr<IDXGISwapChain4> pSwapChain;

		ComPtr<ID3D12Resource> ppBackBuffers[BufferCount];
		D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle[BufferCount];
	};
}