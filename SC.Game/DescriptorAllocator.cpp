using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

ComPtr<ID3D12DescriptorHeap> DescriptorAllocator::mDescriptorHeap;
UINT DescriptorAllocator::mCapacity;
Mutex DescriptorAllocator::mLocker;

UINT DescriptorAllocator::mHandleStride;
D3D12_CPU_DESCRIPTOR_HANDLE DescriptorAllocator::mHandleBase;
queue<UINT> DescriptorAllocator::mQueue;

bool DescriptorAllocator::mDisposed = false;

void DescriptorAllocator::Initialize()
{
	App::Disposing.push_front( OnDisposing );

	Realloc( 512 );
}

void DescriptorAllocator::Push( UINT index )
{
	auto lock = mLocker.Lock();
	mQueue.push( index );
}

CShaderResourceView DescriptorAllocator::CreateShaderResourceView( ID3D12Resource* pResource, const D3D12_SHADER_RESOURCE_VIEW_DESC* pSRVDesc )
{
	auto lock = mLocker.Lock();
	auto pDevice = Graphics::mDevice->pDevice.Get();

	if ( mQueue.empty() )
	{
		Realloc( mCapacity + 512 );
	}

	auto index = mQueue.front();
	mQueue.pop();

	auto handle = mHandleBase;
	handle.ptr += mHandleStride * index;

	pDevice->CreateShaderResourceView( pResource, pSRVDesc, handle );

	return index;
}

CShaderResourceView DescriptorAllocator::CreateUnorderedAccessView( ID3D12Resource* pResource, const D3D12_UNORDERED_ACCESS_VIEW_DESC* pUAVDesc )
{
	auto lock = mLocker.Lock();
	auto pDevice = Graphics::mDevice->pDevice.Get();

	if ( mQueue.empty() )
	{
		Realloc( mCapacity + 512 );
	}

	auto index = mQueue.front();
	mQueue.pop();

	auto handle = mHandleBase;
	handle.ptr += mHandleStride * index;

	pDevice->CreateUnorderedAccessView( pResource, nullptr, pUAVDesc, handle );

	return index;
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorAllocator::GetHandle( UINT index )
{
	auto handle = mHandleBase;
	handle.ptr += index * mHandleStride;

	return handle;
}

void DescriptorAllocator::OnDisposing()
{
	mDescriptorHeap.Reset();
	mDisposed = true;
}

void DescriptorAllocator::Realloc( UINT newCapacity )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{ };
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.NumDescriptors = newCapacity;

	// ���ο� ������ �� ��ü�� �����մϴ�.
	ComPtr<ID3D12DescriptorHeap> pDescriptorHeap;
	HR( pDevice->CreateDescriptorHeap( &heapDesc, IID_PPV_ARGS( &pDescriptorHeap ) ) );

	// ���� �����ڰ� ���� ��� ���� �����ڿ��� ��� �����͸� �����մϴ�.
	if ( mDescriptorHeap )
	{
		pDevice->CopyDescriptorsSimple( min( mCapacity, newCapacity ), pDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), mDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
	}

	// ť�� ���ο� ����� ä��ϴ�.
	for ( UINT i = mCapacity; i < newCapacity; ++i )
	{
		mQueue.push( i );
	}

	// ���� ������ ���� ���ο� ������ ���� ��ȯ�մϴ�.
	mDescriptorHeap.Swap( pDescriptorHeap );
	mCapacity = newCapacity;

	mHandleBase = mDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	mHandleStride = pDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
}