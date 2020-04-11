using namespace SC;
using namespace SC::Game;

HDRBuffer::HDRBuffer()
{

}

void HDRBuffer::OMSetRenderTargets( CDeviceContext& deviceContext )
{
	float clear[4]{ };

	auto rtvHandle = pRTVHeap->GetCPUDescriptorHandleForHeapStart();

	// �ڿ��� ���¸� ���� Ÿ������ �����մϴ�.
	deviceContext.TransitionBarrier(
		pHDRBuffer.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, 0
	);

	// ���� Ÿ�� �並 �����մϴ�.
	deviceContext.OMSetRenderTargets( 1, &rtvHandle, TRUE, nullptr );

	// ���� Ÿ���� ���� �ʱ�ȭ�մϴ�.
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
	// �ڿ��� ���¸� �ȼ� ���̴� �ڿ����� �����մϴ�.
	deviceContext.TransitionBarrier(
		pHDRBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 0
	);
}

void HDRBuffer::ResizeBuffers( int width, int height )
{
	D3D12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_DEFAULT };
	const D3D12_RESOURCE_STATES initState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	auto pDevice = Graphics::mDevice->pDevice.Get();

	// �⺻ �ؽ�ó ������ �����մϴ�.
	D3D12_RESOURCE_DESC textureDesc{ };
	textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.DepthOrArraySize = 1;
	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc = { 1, 0 };
	textureDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

	// �⺻ Ŭ���� ������ �����մϴ�.
	D3D12_CLEAR_VALUE clearValue{ };

	// ���۸� �����մϴ�.
	textureDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	clearValue.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, initState, &clearValue, IID_PPV_ARGS( &pHDRBuffer ) ) );

	// �����ڸ� �����մϴ�.
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

	// ���� Ÿ�� ������ ���� �����մϴ�.
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{ };
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = 1;
	HR( pDevice->CreateDescriptorHeap( &heapDesc, IID_PPV_ARGS( &pRTVHeap ) ) );

	// �������� ũ�⸦ ��ȸ�մϴ�.
	rtvStride = pDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

	return *this;
}