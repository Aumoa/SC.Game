#pragma once

#include "VisibleDescriptorAllocator.h"

namespace SC::Game
{
	class CShaderResourceView;
	class LargeHeap;

	class CDeviceContext
	{
		int mFrameIndex = -1;

	public:
		D3D12_COMMAND_LIST_TYPE mType;

		ComPtr<ID3D12CommandAllocator> mCommandAllocators[2];
		ComPtr<ID3D12GraphicsCommandList> mCommandList;

		VisibleDescriptorAllocator mVisibleDescriptorAllocators[2];

		std::queue<ComPtr<IUnknown>> mGCItems;
		ComPtr<LargeHeap> mShaderDispatchUI;

		bool mSimplify = false;

	public:
		CDeviceContext();
		CDeviceContext( D3D12_COMMAND_LIST_TYPE type );
		CDeviceContext( D3D12_COMMAND_LIST_TYPE type, bool simplify );
		CDeviceContext( CDeviceContext&& from );
		CDeviceContext( const CDeviceContext& ) = delete;

		void Dispose();
		void Reset( int frameIndex, ID3D12PipelineState* pInitialPipelineState = nullptr );
		void Close();

		void GCAdd( ComPtr<IUnknown>&& pUnknown );
		void GCFlush( ID3D12Fence* pFence, UINT64 fenceValue );

		void SetPipelineState( ID3D12PipelineState* pPipelineState );
		void SetGraphicsRootSignature( ID3D12RootSignature* pRootSignature );
		void SetComputeRootSignature( ID3D12RootSignature* pRootSignature );
		void CopyBufferRegion( ID3D12Resource* pDstBuffer, UINT64 dstOffset, ID3D12Resource* pSrcBuffer, UINT64 srcOffset, UINT64 numBytes );
		void ResourceBarrier( UINT numBarriers, const D3D12_RESOURCE_BARRIER* pResourceBarriers );
		void SetGraphicsRootConstantBufferView( UINT index, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation );
		void SetGraphicsRoot32BitConstant( UINT index, UINT srcData, UINT destOffsetIn32BitValues = 0 );
		void SetGraphicsRoot32BitConstants( UINT index, UINT num32BitValuesToSet, const void* pSrcData, UINT destOffsetIn32BitValues = 0 );
		void DrawInstanced( UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation = 0, UINT startInstanceLocation = 0 );
		void IASetPrimitiveTopology( D3D12_PRIMITIVE_TOPOLOGY primitiveTopology );
		void ClearRenderTargetView( D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView, const FLOAT colorRGBA[4], UINT numRects, const D3D12_RECT* pRects );
		void OMSetRenderTargets( UINT numRenderTargetDescriptors, const D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors, BOOL rtsSingleHandleToDescriptorRange, const D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor );
		void SetGraphicsRootShaderResourceView( UINT index, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation );
		void RSSetViewports( UINT numViewports, const D3D12_VIEWPORT* pViewports );
		void RSSetScissorRects( UINT numRects, const D3D12_RECT* pRects );
		void SetGraphicsRootShaderResource( UINT index, CShaderResourceView& shaderResourceView );
		void CopyResource( ID3D12Resource* pDstResource, ID3D12Resource* pSrcResource );
		void ClearDepthStencilView( const D3D12_CPU_DESCRIPTOR_HANDLE& depthStencilView, D3D12_CLEAR_FLAGS clearFlags = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, float depth = 1.0f, UINT8 stencil = 0, UINT numRects = 0, const D3D12_RECT* pRects = nullptr );
		void SetGraphicsRootShaderResource( UINT index, UINT numShaderResources, CShaderResourceView* pShaderResourceViews );
		void SetGraphicsRootShaderResource( UINT index, UINT numShaderResources, CShaderResourceView** ppShaderResourceViews );
		void IASetVertexBuffers( UINT startSlot, UINT numViews, const D3D12_VERTEX_BUFFER_VIEW* pViews );
		void IASetIndexBuffer( const D3D12_INDEX_BUFFER_VIEW* pView );
		void DrawIndexedInstanced( UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation );
		void CopyTextureRegion( const D3D12_TEXTURE_COPY_LOCATION* pDst, UINT dstX, UINT dstY, UINT dstZ, const D3D12_TEXTURE_COPY_LOCATION* pSrc, const D3D12_BOX* pSrcBox );
		void SetComputeRoot32BitConstant( UINT index, UINT srcData, UINT destOffsetIn32BitValues = 0 );
		void SetComputeRoot32BitConstants( UINT index, UINT num32BitValuesToSet, const void* pSrcData, UINT destOffsetIn32BitValues );
		void SetComputeRootShaderResource( UINT index, CShaderResourceView& shaderResourceView );
		void SetComputeRootShaderResource( UINT index, UINT numShaderResources, CShaderResourceView* pShaderResourceViews );
		void SetComputeRootShaderResource( UINT index, UINT numShaderResources, CShaderResourceView** ppShaderResourceViews );
		void Dispatch( UINT threadGroupCountX, UINT threadGroupCountY, UINT threadGroupCountZ = 1 );
		void SetComputeRootShaderResourceView( UINT index, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation );
		void SetComputeRootUnorderedAccessView( UINT index, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation );

		void ClearRenderTargetView( D3D12_CPU_DESCRIPTOR_HANDLE renderTargetView, const std::array<FLOAT, 4>& colorRGBA, UINT numRects = 0, const D3D12_RECT* pRects = nullptr )
		{
			return ClearRenderTargetView( renderTargetView, colorRGBA.data(), numRects, pRects );
		}

		template< int Count >
		void TransitionBarrier( ID3D12Resource* ( &ppResources )[Count], D3D12_RESOURCE_STATES( &pStatesBefore )[Count], D3D12_RESOURCE_STATES( &pStatesAfter )[Count], int( &pSubresourceIndexes )[Count] )
		{
			D3D12_RESOURCE_BARRIER barriers[Count]{ };

			for ( int i = 0; i < Count; ++i )
			{
				barriers[i].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				barriers[i].Transition.pResource = ppResources[i];
				barriers[i].Transition.StateBefore = pStatesBefore[i];
				barriers[i].Transition.StateAfter = pStatesAfter[i];
				if ( pSubresourceIndexes ) barriers[i].Transition.Subresource = pSubresourceIndexes[i];
			}

			mCommandList->ResourceBarrier( Count, barriers );
		}

		template< class... _Args >
		void TransitionBarrier( ID3D12Resource* pResource, D3D12_RESOURCE_STATES StateBefore, D3D12_RESOURCE_STATES StateAfter, int SubresourceIndex, _Args... args )
		{
			constexpr int sizeOf = 1 + sizeof...( _Args ) / 4;
			ID3D12Resource* ppResources[sizeOf];
			D3D12_RESOURCE_STATES pBeforeStates[sizeOf];
			D3D12_RESOURCE_STATES pAfterStates[sizeOf];
			int pSubresourceIndexes[sizeOf];

			TransitionBarrier_Helper( ppResources, pBeforeStates, pAfterStates, pSubresourceIndexes, pResource, StateBefore, StateAfter, SubresourceIndex, args... );

			TransitionBarrier( ppResources, pBeforeStates, pAfterStates, pSubresourceIndexes );
		}

		CDeviceContext& operator=( CDeviceContext&& from );

	private:
		template< class... _Args >
		inline void TransitionBarrier_Helper( ID3D12Resource** ppResources, D3D12_RESOURCE_STATES* pBeforeStates, D3D12_RESOURCE_STATES* pAfterStates, int* pSubresourceIndexes, ID3D12Resource* pResource, D3D12_RESOURCE_STATES StateBefore, D3D12_RESOURCE_STATES StateAfter, int SubresourceIndex, _Args... args )
		{
			*ppResources++ = pResource;
			*pBeforeStates++ = StateBefore;
			*pAfterStates++ = StateAfter;
			*pSubresourceIndexes++ = SubresourceIndex;

			TransitionBarrier_Helper( ppResources, pBeforeStates, pAfterStates, pSubresourceIndexes, args... );
		}

		inline void TransitionBarrier_Helper( ID3D12Resource** ppResources, D3D12_RESOURCE_STATES* pBeforeStates, D3D12_RESOURCE_STATES* pAfterStates, int* pSubresourceIndexes, ID3D12Resource* pResource, D3D12_RESOURCE_STATES StateBefore, D3D12_RESOURCE_STATES StateAfter, int SubresourceIndex )
		{
			*ppResources++ = pResource;
			*pBeforeStates++ = StateBefore;
			*pAfterStates++ = StateAfter;
			*pSubresourceIndexes++ = SubresourceIndex;
		}
	};
}