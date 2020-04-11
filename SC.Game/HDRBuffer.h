#pragma once

namespace SC::Game
{
	class HDRBuffer
	{
	public:
		ComPtr<ID3D12Resource> pHDRBuffer;

		ComPtr<ID3D12DescriptorHeap> pRTVHeap;

		D3D12_VIEWPORT viewport{ };
		D3D12_RECT scissor{ };
		UINT rtvStride = 0;

		UINT width = 0;
		UINT height = 0;

		CShaderResourceView ppShaderResourceViews[1];

	public:
		HDRBuffer();

		void OMSetRenderTargets( CDeviceContext& deviceContext );
		void SetGraphicsRootShaderResources( CDeviceContext& deviceContext );
		void SetComputeRootShaderResources( CDeviceContext& deviceContext );
		void EndDraw( CDeviceContext& deviceContext );

		void ResizeBuffers( int width, int height );
		void Dispose();

		HDRBuffer& operator=( HDRBuffer&& );
	};
}