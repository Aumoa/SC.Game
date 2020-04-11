using namespace SC;
using namespace SC::Game;

#pragma unmanaged

ImmutableHeap::ImmutableHeap( UINT64 sizeInBytes, const void* pData )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_DEFAULT };

	D3D12_RESOURCE_DESC bufferDesc{ };
	bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	bufferDesc.Width = sizeInBytes;
	bufferDesc.Height = 1;
	bufferDesc.DepthOrArraySize = 1;
	bufferDesc.MipLevels = 1;
	bufferDesc.SampleDesc = { 1, 0 };
	bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS( &mResource ) ) );

	ComPtr<ID3D12Resource> pUpload;
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS( &pUpload ) ) );

	void* block;
	HR( pUpload->Map( 0, nullptr, &block ) );
	memcpy( block, pData, sizeInBytes );
	pUpload->Unmap( 0, nullptr );

	CDeviceContext deviceContext( D3D12_COMMAND_LIST_TYPE_COPY, true );
	deviceContext.Reset( 0 );
	deviceContext.CopyResource( mResource.Get(), pUpload.Get() );
	deviceContext.Close();

	Graphics::mCopyQueue->Execute( deviceContext );
	auto signal = Graphics::mCopyQueue->Signal();

	HEvent hEvent;
	Graphics::mCopyQueue->SetEventOnCompletion( signal, hEvent );
	hEvent.WaitForSingleObject();
}

HRESULT STDMETHODCALLTYPE ImmutableHeap::QueryInterface( REFIID riid, _COM_Outptr_ void** ppvObject )
{
	if ( riid == IID_IUnknown )
	{
		*ppvObject = dynamic_cast< IUnknown* >( this );
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE ImmutableHeap::AddRef()
{
	return ( ULONG )InterlockedIncrement64( ( volatile LONG64* )&mRefCount );
}

ULONG STDMETHODCALLTYPE ImmutableHeap::Release()
{
	auto c = InterlockedDecrement64( ( volatile LONG64* )&mRefCount );
	if ( c == 0 )
	{
		delete this;
		return 0;
	}
	else
	{
		return ( ULONG )c;
	}
}

D3D12_GPU_VIRTUAL_ADDRESS ImmutableHeap::GetGPUVirtualAddress()
{
	return mResource->GetGPUVirtualAddress();
}

ID3D12Resource* ImmutableHeap::GetResource()
{
	return mResource.Get();
}