#pragma once

namespace SC::Game
{
	class GeometryBuffer
	{
	public:
		ComPtr<ID3D12Resource> pColorBuffer;
		ComPtr<ID3D12Resource> pNormalBuffer;
		ComPtr<ID3D12Resource> pMaterialBuffer;
		ComPtr<ID3D12Resource> pDepthBuffer;

		ComPtr<ID3D12DescriptorHeap> pRTVHeap;
		ComPtr<ID3D12DescriptorHeap> pDSVHeap;

		D3D12_VIEWPORT viewport{ };
		D3D12_RECT scissor{ };
		UINT rtvStride = 0;

		UINT width = 0;
		UINT height = 0;

		CShaderResourceView ppShaderResourceViews[4];

	public:
		GeometryBuffer();

		void OMSetRenderTargets( CDeviceContext& deviceContext );
		void EndDraw( CDeviceContext& deviceContext );

		void ResizeBuffers( int width, int height );
		void Dispose();

		GeometryBuffer& operator=( GeometryBuffer&& );
	};
}