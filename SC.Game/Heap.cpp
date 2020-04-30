using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

Heap::Heap( AlignedHeap* pHeapRef, UINT64 index )
{
	mRefCount = 0;

	mHeapRef = pHeapRef;
	mIndex = index;
}

Heap::~Heap()
{
	if ( mHeapRef && mIndex )
	{
		mHeapRef->Free( mIndex );
	}
}

HRESULT STDMETHODCALLTYPE Heap::QueryInterface( REFIID riid, _COM_Outptr_ void** ppvObject )
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

ULONG STDMETHODCALLTYPE Heap::AddRef()
{
	return ( ULONG )InterlockedIncrement64( ( volatile LONG64* )&mRefCount );
}

ULONG STDMETHODCALLTYPE Heap::Release()
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

void* Heap::Map()
{
	return mHeapRef->GetUploadAddress( App::mFrameIndex, mIndex );
}

void* Heap::Map( int frameIndex )
{
	return mHeapRef->GetUploadAddress( frameIndex, mIndex );
}

void Heap::Unmap()
{
	D3D12_RANGE range;
	range.Begin = mIndex * mHeapRef->mAlign;
	range.End = range.Begin + mHeapRef->mAlign;
	mHeapRef->AddCopyRange( App::mFrameIndex, range );
}

void Heap::Unmap( int frameIndex )
{
	D3D12_RANGE range;
	range.Begin = mIndex * mHeapRef->mAlign;
	range.End = range.Begin + mHeapRef->mAlign;
	mHeapRef->AddCopyRange( frameIndex, range );
}

D3D12_GPU_VIRTUAL_ADDRESS Heap::GetGPUVirtualAddress()
{
	return mHeapRef->GetVirtualAddress( mIndex );
}

ID3D12Resource* Heap::GetResource()
{
	return mHeapRef->pResource.Get();
}