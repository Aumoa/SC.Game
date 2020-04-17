#pragma once

namespace SC::Game
{
	class HDRComputedBuffer
	{
	public:
		struct HDRConstants
		{
			float AvgLuminance;
		};

		ComPtr<ID3D12Resource> pHDRHalfBuffer;
		ComPtr<ID3D12Resource> pHDRConstants;
		int mHalfSize[2];

		CShaderResourceView pUnorderedAccessViews[2];

	public:
		HDRComputedBuffer();

		void SetComputeRootTimestamp( CDeviceContext& deviceContext, float time );
		void SetGraphicsRootConstantBuffers( CDeviceContext& deviceContext );
		void Compute( CDeviceContext& deviceContext, int pass );

		void ResizeBuffers( int width, int height );
		void Dispose();

		HDRComputedBuffer& operator=( HDRComputedBuffer&& );
	};
}