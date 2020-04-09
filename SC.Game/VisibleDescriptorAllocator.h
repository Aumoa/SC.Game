#pragma once

namespace SC::Game
{
	class VisibleDescriptorAllocator
	{
		VisibleDescriptorAllocator( const VisibleDescriptorAllocator& ) = delete;

	public:
		ComPtr<ID3D12DescriptorHeap> mDescriptorHeap;
		D3D12_GPU_DESCRIPTOR_HANDLE mGPUHandleBase;
		D3D12_CPU_DESCRIPTOR_HANDLE mCPUHandleBase;

		std::vector<UINT> mDescriptorIndexes;
		UINT mSize = 0;
		UINT mStride = 0;
		UINT mCapacity = 0;

	public:
		VisibleDescriptorAllocator();
		VisibleDescriptorAllocator( UINT capacity );
		VisibleDescriptorAllocator( VisibleDescriptorAllocator&& right );

		void Reset( CDeviceContext& deviceContext );
		UINT CopyFrom( UINT index, CDeviceContext& deviceContext );
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle( UINT index );

		VisibleDescriptorAllocator& operator=( VisibleDescriptorAllocator&& right );

	private:
		void Realloc( UINT newCapacity );
	};
}