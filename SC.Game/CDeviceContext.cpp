using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

CDeviceContext::CDeviceContext()
{

}

CDeviceContext::CDeviceContext( D3D12_COMMAND_LIST_TYPE type )
{
	mType = type;

	auto pDevice = Graphics::mDevice->pDevice.Get();

	HR( pDevice->CreateCommandAllocator( mType, IID_PPV_ARGS( &mCommandAllocators[0] ) ) );
	HR( pDevice->CreateCommandAllocator( mType, IID_PPV_ARGS( &mCommandAllocators[1] ) ) );

	mVisibleDescriptorAllocators[0] = VisibleDescriptorAllocator( 512 );
	mVisibleDescriptorAllocators[1] = VisibleDescriptorAllocator( 512 );
}

CDeviceContext::CDeviceContext( D3D12_COMMAND_LIST_TYPE type, bool simplify )
{
	mType = type;

	auto pDevice = Graphics::mDevice->pDevice.Get();

	HR( pDevice->CreateCommandAllocator( mType, IID_PPV_ARGS( &mCommandAllocators[0] ) ) );

	mSimplify = simplify;
}

CDeviceContext::CDeviceContext( CDeviceContext&& from )
{
	mType = from.mType;

	mCommandAllocators[0] = move( from.mCommandAllocators[0] );
	mCommandAllocators[1] = move( from.mCommandAllocators[1] );

	mVisibleDescriptorAllocators[0] = move( from.mVisibleDescriptorAllocators[0] );
	mVisibleDescriptorAllocators[1] = move( from.mVisibleDescriptorAllocators[1] );

	mCommandList = move( from.mCommandList );
}

void CDeviceContext::Dispose()
{
	mCommandList.Reset();

	mCommandAllocators[0].Reset();
	mCommandAllocators[1].Reset();
}

void CDeviceContext::Reset( int frameIndex, ID3D12PipelineState* pInitialPipelineState )
{
	HR( mCommandAllocators[frameIndex]->Reset() );

	if ( mCommandList )
	{
		HR( mCommandList->Reset( mCommandAllocators[frameIndex].Get(), pInitialPipelineState ) );
	}
	else
	{
		auto pDevice = Graphics::mDevice->pDevice.Get();

		HR( pDevice->CreateCommandList( 0, mType, mCommandAllocators[frameIndex].Get(), pInitialPipelineState, IID_PPV_ARGS( &mCommandList ) ) );
	}

	mFrameIndex = frameIndex;

	if ( !mSimplify )
	{
		mVisibleDescriptorAllocators[frameIndex].Reset( *this );
	}
}

void CDeviceContext::Close()
{
	HR( mCommandList->Close() );
}

void CDeviceContext::GCAdd( ComPtr<IUnknown>&& pUnknown )
{
	mGCItems.push( move( pUnknown ) );
}

void CDeviceContext::GCFlush( ID3D12Fence* pFence, UINT64 fenceValue )
{
	while ( mGCItems.size() )
	{
		GC::Add( pFence, fenceValue, move( mGCItems.front() ) );
		mGCItems.pop();
	}
}

void CDeviceContext::SetPipelineState( ID3D12PipelineState* pPipelineState )
{
	mCommandList->SetPipelineState( pPipelineState );
}

void CDeviceContext::SetGraphicsRootSignature( ID3D12RootSignature* pRootSignature )
{
	mCommandList->SetGraphicsRootSignature( pRootSignature );
}

void CDeviceContext::SetComputeRootSignature( ID3D12RootSignature* pRootSignature )
{
	mCommandList->SetComputeRootSignature( pRootSignature );
}

void CDeviceContext::CopyBufferRegion( ID3D12Resource* pDstBuffer, UINT64 dstOffset, ID3D12Resource* pSrcBuffer, UINT64 srcOffset, UINT64 numBytes )
{
	mCommandList->CopyBufferRegion( pDstBuffer, dstOffset, pSrcBuffer, srcOffset, numBytes );
}

void CDeviceContext::ResourceBarrier( UINT numBarriers, const D3D12_RESOURCE_BARRIER* pResourceBarriers )
{
	mCommandList->ResourceBarrier( numBarriers, pResourceBarriers );
}

void CDeviceContext::SetGraphicsRootConstantBufferView( UINT index, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation )
{
	mCommandList->SetGraphicsRootConstantBufferView( index, bufferLocation );
}

void CDeviceContext::SetGraphicsRoot32BitConstant( UINT index, UINT srcData, UINT destOffsetIn32BitValues )
{
	mCommandList->SetGraphicsRoot32BitConstant( index, srcData, destOffsetIn32BitValues );
}

void CDeviceContext::SetGraphicsRoot32BitConstants( UINT index, UINT num32BitValuesToSet, const void* pSrcData, UINT destOffsetIn32BitValues )
{
	mCommandList->SetGraphicsRoot32BitConstants( index, num32BitValuesToSet, pSrcData, destOffsetIn32BitValues );
}

void CDeviceContext::DrawInstanced( UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation, UINT startInstanceLocation )
{
	mCommandList->DrawInstanced( vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation );
}

void CDeviceContext::IASetPrimitiveTopology( D3D12_PRIMITIVE_TOPOLOGY primitiveTopology )
{
	mCommandList->IASetPrimitiveTopology( primitiveTopology );
}

void CDeviceContext::ClearRenderTargetView( D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView, const FLOAT colorRGBA[4], UINT numRects, const D3D12_RECT* pRects )
{
	mCommandList->ClearRenderTargetView( renderTargetView, colorRGBA, numRects, pRects );
}

void CDeviceContext::OMSetRenderTargets( UINT numRenderTargetDescriptors, const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors, BOOL rtsSingleHandleToDescriptorRange, const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor )
{
	mCommandList->OMSetRenderTargets( numRenderTargetDescriptors, pRenderTargetDescriptors, rtsSingleHandleToDescriptorRange, pDepthStencilDescriptor );
}

void CDeviceContext::SetGraphicsRootShaderResourceView( UINT index, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation )
{
	mCommandList->SetGraphicsRootShaderResourceView( index, bufferLocation );
}

void CDeviceContext::RSSetViewports( UINT numViewports, const D3D12_VIEWPORT* pViewports )
{
	mCommandList->RSSetViewports( numViewports, pViewports );
}

void CDeviceContext::RSSetScissorRects( UINT numRects, const D3D12_RECT* pRects )
{
	mCommandList->RSSetScissorRects( numRects, pRects );
}

void CDeviceContext::SetGraphicsRootShaderResource( UINT index, CShaderResourceView& shaderResourceView )
{
	auto idx = mVisibleDescriptorAllocators[mFrameIndex].CopyFrom( shaderResourceView.mIndex, *this );
	auto handle = mVisibleDescriptorAllocators[mFrameIndex].GetGPUHandle( idx );

	mCommandList->SetGraphicsRootDescriptorTable( index, handle );
}

void CDeviceContext::CopyResource( ID3D12Resource* pDstResource, ID3D12Resource* pSrcResource )
{
	mCommandList->CopyResource( pDstResource, pSrcResource );
}

void CDeviceContext::ClearDepthStencilView( const D3D12_CPU_DESCRIPTOR_HANDLE& depthStencilView, D3D12_CLEAR_FLAGS clearFlags, float depth, UINT8 stencil, UINT numRects, const D3D12_RECT* pRects )
{
	mCommandList->ClearDepthStencilView( depthStencilView, clearFlags, depth, stencil, numRects, pRects );
}

void CDeviceContext::SetGraphicsRootShaderResource( UINT index, UINT numShaderResources, CShaderResourceView* pShaderResourceViews )
{
	UINT start = -1;

	for ( UINT i = 0; i < numShaderResources; ++i )
	{
		auto idx = mVisibleDescriptorAllocators[mFrameIndex].CopyFrom( pShaderResourceViews[i].mIndex, *this );
		if ( start == -1 ) start = idx;
	}

	auto handle = mVisibleDescriptorAllocators[mFrameIndex].GetGPUHandle( start );
	mCommandList->SetGraphicsRootDescriptorTable( index, handle );
}

void CDeviceContext::IASetVertexBuffers( UINT startSlot, UINT numViews, const D3D12_VERTEX_BUFFER_VIEW* pViews )
{
	mCommandList->IASetVertexBuffers( startSlot, numViews, pViews );
}

void CDeviceContext::IASetIndexBuffer( const D3D12_INDEX_BUFFER_VIEW* pView )
{
	mCommandList->IASetIndexBuffer( pView );
}

void CDeviceContext::DrawIndexedInstanced( UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation )
{
	mCommandList->DrawIndexedInstanced( indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation );
}

CDeviceContext& CDeviceContext::operator=( CDeviceContext&& from )
{
	mType = from.mType;

	mCommandAllocators[0] = move( from.mCommandAllocators[0] );
	mCommandAllocators[1] = move( from.mCommandAllocators[1] );

	mVisibleDescriptorAllocators[0] = move( from.mVisibleDescriptorAllocators[0] );
	mVisibleDescriptorAllocators[1] = move( from.mVisibleDescriptorAllocators[1] );

	mCommandList = move( from.mCommandList );

	return *this;
}