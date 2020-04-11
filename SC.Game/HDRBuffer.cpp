using namespace SC;
using namespace SC::Game;

HDRBuffer::HDRBuffer()
{

}

void HDRBuffer::OMSetRenderTargets( CDeviceContext& deviceContext )
{
	float clear[4]{ };

	auto rtvHandle = pRTVHeap->GetCPUDescriptorHandleForHeapStart();

	// 자원의 상태를 렌더 타겟으로 변경합니다.
	deviceContext.TransitionBarrier(
		pHDRBuffer.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, 0
	);

	// 렌더 타겟 뷰를 설정합니다.
	deviceContext.OMSetRenderTargets( 1, &rtvHandle, TRUE, nullptr );

	// 렌더 타겟의 색을 초기화합니다.
	deviceContext.ClearRenderTargetView( rtvHandle, clear, 0, nullptr );

	deviceContext.RSSetViewports( 1, &viewport );
	deviceContext.RSSetScissorRects( 1, &scissor );
}

void HDRBuffer::SetGraphicsRootShaderResources( CDeviceContext& deviceContext )
{
	//deviceContext->SetGraphicsRootShaderResources( deviceContext->Slot["HDRBuffer"], 1, ppShaderResourceViews );
}

void HDRBuffer::SetComputeRootShaderResources( CDeviceContext& deviceContext )
{
	//deviceContext->SetComputeRootShaderResources( deviceContext->Slot["HDRBuffer"], 1, ppShaderResourceViews );
}

void HDRBuffer::EndDraw( CDeviceContext& deviceContext )
{
	// 자원의 상태를 픽셀 셰이더 자원으로 변경합니다.
	deviceContext.TransitionBarrier(
		pHDRBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 0
	);
}

void HDRBuffer::ResizeBuffers( int width, int height )
{
	D3D12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_DEFAULT };
	const D3D12_RESOURCE_STATES initState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	auto pDevice = Graphics::mDevice->pDevice.Get();

	// 기본 텍스처 정보를 생성합니다.
	D3D12_RESOURCE_DESC textureDesc{ };
	textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.DepthOrArraySize = 1;
	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc = { 1, 0 };
	textureDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

	// 기본 클리어 정보를 생성합니다.
	D3D12_CLEAR_VALUE clearValue{ };

	// 버퍼를 생성합니다.
	textureDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	clearValue.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, initState, &clearValue, IID_PPV_ARGS( &pHDRBuffer ) ) );

	// 서술자를 생성합니다.
	auto handleBase = pRTVHeap->GetCPUDescriptorHandleForHeapStart();
	pDevice->CreateRenderTargetView( pHDRBuffer.Get(), nullptr, handleBase );

	ppShaderResourceViews[0] = DescriptorAllocator::CreateShaderResourceView( pHDRBuffer.Get(), nullptr );

	viewport.Width = ( float )width;
	viewport.Height = ( float )height;
	viewport.MaxDepth = 1.0f;

	scissor.right = ( int )width;
	scissor.bottom = ( int )height;

	this->width = width;
	this->height = height;

#if defined( _DEBUG )
	pHDRBuffer->SetName( L"HDRBuffer.pHDRBuffer" );
#endif
}

void HDRBuffer::Dispose()
{
	pHDRBuffer.Reset();

	pRTVHeap.Reset();

	ppShaderResourceViews[0] = CShaderResourceView();
}

HDRBuffer& HDRBuffer::operator=( HDRBuffer&& )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	// 렌더 타겟 서술자 힙을 생성합니다.
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{ };
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = 1;
	HR( pDevice->CreateDescriptorHeap( &heapDesc, IID_PPV_ARGS( &pRTVHeap ) ) );

	// 서술자의 크기를 조회합니다.
	rtvStride = pDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

	return *this;
}