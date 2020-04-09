#pragma once

namespace SC::Game
{
	class AlignedHeap;

	class Heap : public IUnknown
	{
		UINT64 mRefCount = 0;

	public:
		AlignedHeap* mHeapRef;
		UINT64 mIndex;

	public:
		Heap( AlignedHeap* pHeapRef, UINT64 index );
		virtual ~Heap();

		HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, _COM_Outptr_ void** ppvObject ) override;
		ULONG STDMETHODCALLTYPE AddRef() override;
		ULONG STDMETHODCALLTYPE Release() override;

		void* Map();
		void* Map( int frameIndex );
		void Unmap();
		void Unmap( int frameIndex );
		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress();
		ID3D12Resource* GetResource();
	};
}