using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

VisibleDescriptorAllocator::VisibleDescriptorAllocator()
{

}

VisibleDescriptorAllocator::VisibleDescriptorAllocator( UINT capacity )
{
	Realloc( 512 );
}

VisibleDescriptorAllocator::VisibleDescriptorAllocator( VisibleDescriptorAllocator&& right )
{
	mDescriptorHeap = move( right.mDescriptorHeap );
	mGPUHandleBase = right.mGPUHandleBase;
	mCPUHandleBase = right.mCPUHandleBase;

	mDescriptorIndexes = move( right.mDescriptorIndexes );
	mSize = right.mSize;
	mStride = right.mStride;
	mCapacity = right.mCapacity;
}

void VisibleDescriptorAllocator::Reset( CDeviceContext& deviceContext )
{
	mSize = 0;

	deviceContext.mCommandList->SetDescriptorHeaps( 1, mDescriptorHeap.GetAddressOf() );
}

UINT VisibleDescriptorAllocator::CopyFrom( UINT index, CDeviceContext& deviceContext )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	if ( mSize >= mCapacity )
	{
		Realloc( mCapacity + 512 );
		deviceContext.mCommandList->SetDescriptorHeaps( 1, mDescriptorHeap.GetAddressOf() );
	}

	mDescriptorIndexes[mSize] = index;

	auto handleBase = mCPUHandleBase;
	handleBase.ptr += mStride * mSize;
	pDevice->CopyDescriptorsSimple( 1, handleBase, DescriptorAllocator::GetHandle( mDescriptorIndexes[mSize] ), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );

	auto idx = mSize;
	mSize += 1;

	return idx;
}

D3D12_GPU_DESCRIPTOR_HANDLE VisibleDescriptorAllocator::GetGPUHandle( UINT index )
{
	auto handle = mGPUHandleBase;
	handle.ptr += mStride * index;
	return handle;
}

VisibleDescriptorAllocator& VisibleDescriptorAllocator::operator=( VisibleDescriptorAllocator&& right )
{
	mDescriptorHeap = move( right.mDescriptorHeap );
	mGPUHandleBase = right.mGPUHandleBase;
	mCPUHandleBase = right.mCPUHandleBase;

	mDescriptorIndexes = move( right.mDescriptorIndexes );
	mSize = right.mSize;
	mStride = right.mStride;
	mCapacity = right.mCapacity;

	return *this;
}

void VisibleDescriptorAllocator::Realloc( UINT newCapacity )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	mStride = pDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );

	// 새 서술자 힙을 할당합니다.
	ComPtr<ID3D12DescriptorHeap> pDescriptorHeap;
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{ };
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.NumDescriptors = newCapacity;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	HR( pDevice->CreateDescriptorHeap( &heapDesc, IID_PPV_ARGS( &pDescriptorHeap ) ) );

	// 기존 서술자가 있을 경우 기존의 서술자를 복사합니다.
	if ( mDescriptorHeap && mDescriptorIndexes.size() )
	{
		auto handleBase = pDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		for ( UINT i = 0; i < mSize; ++i )
		{
			pDevice->CopyDescriptorsSimple( 1, handleBase, DescriptorAllocator::GetHandle( mDescriptorIndexes[i] ), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );
		}
	}

	// 기존 서술자와 교체합니다.
	mDescriptorHeap.Swap( pDescriptorHeap );
	mGPUHandleBase = mDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	mCPUHandleBase = mDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	// 기존 서술자 힙을 가비지 컬렉터로 보냅니다.
	App::GCAdd( pDescriptorHeap );

	mCapacity = newCapacity;
	mDescriptorIndexes.resize( mCapacity );
}