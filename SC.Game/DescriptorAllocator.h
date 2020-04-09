#pragma once

namespace SC::Game
{
	class DescriptorAllocator
	{
	public:
		static ComPtr<ID3D12DescriptorHeap> mDescriptorHeap;
		static UINT mCapacity;
		static Mutex mLocker;

		static UINT mHandleStride;
		static D3D12_CPU_DESCRIPTOR_HANDLE mHandleBase;
		static std::queue<UINT> mQueue;

	public:
		static void Initialize();
		static void Push( UINT index );

		static CShaderResourceView CreateShaderResourceView( ID3D12Resource* pResource, const D3D12_SHADER_RESOURCE_VIEW_DESC* pSRVDesc );
		static D3D12_CPU_DESCRIPTOR_HANDLE GetHandle( UINT index );

	private:
		static void OnDisposing();

		static void Realloc( UINT newCapacity );
	};
}