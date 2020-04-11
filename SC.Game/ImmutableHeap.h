#pragma once

namespace SC::Game
{
	class ImmutableHeap : public IUnknown
	{
		UINT64 mRefCount = 0;

	public:
		ComPtr<ID3D12Resource> mResource;
		UINT64 mSizeInBytes = 0;

	public:
		ImmutableHeap( UINT64 sizeInBytes, const void* pData );

		HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, _COM_Outptr_ void** ppvObject ) override;
		ULONG STDMETHODCALLTYPE AddRef() override;
		ULONG STDMETHODCALLTYPE Release() override;

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress();
		ID3D12Resource* GetResource();
	};
}