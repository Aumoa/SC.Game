using namespace SC;
using namespace SC::Game;

#pragma unmanaged

HDRComputedBuffer::HDRComputedBuffer()
{

}

void HDRComputedBuffer::SetComputeRootTimestamp( CDeviceContext& deviceContext, float time )
{
	deviceContext.SetComputeRoot32BitConstant( ( UINT )Slot_HDRCompute_Timer, ( UINT& )time );
}

void HDRComputedBuffer::SetGraphicsRootConstantBuffers( CDeviceContext& deviceContext )
{
	deviceContext.SetGraphicsRootConstantBufferView( ( UINT )Slot_PP_HDRConstants, pHDRConstants->GetGPUVirtualAddress() );
}

void HDRComputedBuffer::Compute( CDeviceContext& deviceContext, int pass )
{
	if ( pass == 0 )
	{
		deviceContext.TransitionBarrier(
			pHDRConstants.Get(), D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, D3D12_RESOURCE_STATE_UNORDERED_ACCESS, 0
		);
		deviceContext.SetComputeRootShaderResource( ( UINT )Slot_HDRCompute_HDRComputedBuffer, 2, pUnorderedAccessViews );

		UINT dispatchX = ( ( UINT )mHalfSize[0] - 1 ) / 32 + 1;
		UINT dispatchY = ( ( UINT )mHalfSize[1] - 1 ) / 32 + 1;
		deviceContext.Dispatch( dispatchX, dispatchY, 1 );
	}
	else if ( pass == 1 )
	{
		UINT dispatchX = 1;
		UINT dispatchY = mHalfSize[1];
		deviceContext.Dispatch( dispatchX, dispatchY, 1 );
	}
	else if ( pass == 2 )
	{
		UINT dispatchX = 1;
		UINT dispatchY = 1;
		deviceContext.Dispatch( dispatchX, dispatchY, 1 );

		deviceContext.TransitionBarrier(
			pHDRConstants.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, 0
		);
	}
}

void HDRComputedBuffer::ResizeBuffers( int width, int height )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	int halfWidth = ( width - 1 ) / 2 + 1;
	int halfHeight = ( height - 1 ) / 2 + 1;

	UINT64 constantsSize =
		sizeof( HDRConstants ) +
		sizeof( float ) * halfHeight;

	D3D12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_DEFAULT };

	D3D12_RESOURCE_DESC bufferDesc{ };
	bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	bufferDesc.Width = constantsSize;
	bufferDesc.Height = 1;
	bufferDesc.DepthOrArraySize = 1;
	bufferDesc.MipLevels = 1;
	bufferDesc.SampleDesc = { 1, 0 };
	bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	bufferDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

	D3D12_RESOURCE_DESC textureDesc = bufferDesc;
	textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureDesc.Width = halfWidth;
	textureDesc.Height = halfHeight;
	textureDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	textureDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	HR( pDevice->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureDesc,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
		nullptr,
		IID_PPV_ARGS( &pHDRHalfBuffer )
	) );

	HR( pDevice->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&bufferDesc,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
		nullptr,
		IID_PPV_ARGS( &pHDRConstants )
	) );

	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc{ };
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.NumElements = halfHeight + 1;
	uavDesc.Buffer.StructureByteStride = sizeof( float );

	pUnorderedAccessViews[0] = DescriptorAllocator::CreateUnorderedAccessView( pHDRHalfBuffer.Get(), nullptr );
	pUnorderedAccessViews[1] = DescriptorAllocator::CreateUnorderedAccessView( pHDRConstants.Get(), &uavDesc );

	mHalfSize[0] = halfWidth;
	mHalfSize[1] = halfHeight;
}