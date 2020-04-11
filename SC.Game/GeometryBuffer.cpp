using namespace SC;
using namespace SC::Game;

using namespace std;

GeometryBuffer::GeometryBuffer()
{

}

void GeometryBuffer::OMSetRenderTargets( CDeviceContext& deviceContext )
{
	float clear[4]{ };

	auto rtvHandle = pRTVHeap->GetCPUDescriptorHandleForHeapStart();
	auto dsvHandle = pDSVHeap->GetCPUDescriptorHandleForHeapStart();

	// �ڿ��� ���¸� ���� Ÿ������ �����մϴ�.
	deviceContext.TransitionBarrier(
		pColorBuffer.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, 0,
		pNormalBuffer.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, 0,
		pMaterialBuffer.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, 0,
		pDepthBuffer.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_DEPTH_WRITE, 0
	);

	// ���� Ÿ�� �並 �����մϴ�.
	deviceContext.OMSetRenderTargets( 3, &rtvHandle, TRUE, &dsvHandle );

	// ���� Ÿ���� ���� �ʱ�ȭ�մϴ�.
	deviceContext.ClearRenderTargetView( rtvHandle, clear, 0, nullptr );
	rtvHandle.ptr += rtvStride;
	deviceContext.ClearRenderTargetView( rtvHandle, clear, 0, nullptr );
	rtvHandle.ptr += rtvStride;
	deviceContext.ClearRenderTargetView( rtvHandle, clear, 0, nullptr );
	deviceContext.ClearDepthStencilView( dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr );

	deviceContext.RSSetViewports( 1, &viewport );
	deviceContext.RSSetScissorRects( 1, &scissor );
}

void GeometryBuffer::EndDraw( CDeviceContext& deviceContext )
{
	// �ڿ��� ���¸� �ȼ� ���̴� �ڿ����� �����մϴ�.
	deviceContext.TransitionBarrier(
		pColorBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 0,
		pNormalBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 0,
		pMaterialBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 0,
		pDepthBuffer.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 0
	);
}

void GeometryBuffer::ResizeBuffers( int width, int height )
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
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	clearValue.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, initState, &clearValue, IID_PPV_ARGS( &pColorBuffer ) ) );

	textureDesc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
	clearValue.Format = DXGI_FORMAT_R11G11B10_FLOAT;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, initState, &clearValue, IID_PPV_ARGS( &pNormalBuffer ) ) );

	textureDesc.Format = DXGI_FORMAT_R16_UINT;
	clearValue.Format = DXGI_FORMAT_R16_UINT;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, initState, &clearValue, IID_PPV_ARGS( &pMaterialBuffer ) ) );

	textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	textureDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	clearValue.Format = DXGI_FORMAT_D32_FLOAT;
	clearValue.DepthStencil.Depth = 1.0f;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, initState, &clearValue, IID_PPV_ARGS( &pDepthBuffer ) ) );

	// ���� ���ٽ� ������ ���� ���ٽ� �� ������ �����մϴ�.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{ DXGI_FORMAT_D32_FLOAT, D3D12_DSV_DIMENSION_TEXTURE2D, D3D12_DSV_FLAG_NONE };
	dsvDesc.Texture2D = { };

	// ���� ���ٽ� ������ ���̴� �ڿ� �� ������ �����մϴ�.
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{ DXGI_FORMAT_R32_FLOAT, D3D12_SRV_DIMENSION_TEXTURE2D, D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING };
	srvDesc.Texture2D = { 0, 1, 0, 0.0f };

	// �����ڸ� �����մϴ�.
	auto handleBase = pRTVHeap->GetCPUDescriptorHandleForHeapStart();
	pDevice->CreateRenderTargetView( pColorBuffer.Get(), nullptr, handleBase );

	handleBase.ptr += rtvStride;
	pDevice->CreateRenderTargetView( pNormalBuffer.Get(), nullptr, handleBase );

	handleBase.ptr += rtvStride;
	pDevice->CreateRenderTargetView( pMaterialBuffer.Get(), nullptr, handleBase );

	handleBase = pDSVHeap->GetCPUDescriptorHandleForHeapStart();
	pDevice->CreateDepthStencilView( pDepthBuffer.Get(), &dsvDesc, handleBase );

	ppShaderResourceViews[0] = DescriptorAllocator::CreateShaderResourceView( pColorBuffer.Get(), nullptr );
	ppShaderResourceViews[1] = DescriptorAllocator::CreateShaderResourceView( pNormalBuffer.Get(), nullptr );
	ppShaderResourceViews[2] = DescriptorAllocator::CreateShaderResourceView( pMaterialBuffer.Get(), nullptr );
	ppShaderResourceViews[3] = DescriptorAllocator::CreateShaderResourceView( pDepthBuffer.Get(), &srvDesc );

	viewport.Width = ( float )width;
	viewport.Height = ( float )height;
	viewport.MaxDepth = 1.0f;

	scissor.right = ( int )width;
	scissor.bottom = ( int )height;

	this->width = width;
	this->height = height;

#if defined( _DEBUG )
	pColorBuffer->SetName( L"GeometryBuffer.pColorBuffer" );
	pNormalBuffer->SetName( L"GeometryBuffer.pNormalBuffer" );
	pMaterialBuffer->SetName( L"GeometryBuffer.pMaterialBuffer" );
	pDepthBuffer->SetName( L"GeometryBuffer.pDepthBuffer" );
#endif
}

void GeometryBuffer::Dispose()
{
	pColorBuffer.Reset();
	pNormalBuffer.Reset();
	pMaterialBuffer.Reset();
	pDepthBuffer.Reset();

	pRTVHeap.Reset();
	pDSVHeap.Reset();

	ppShaderResourceViews[0] = CShaderResourceView();
	ppShaderResourceViews[1] = CShaderResourceView();
	ppShaderResourceViews[2] = CShaderResourceView();
	ppShaderResourceViews[3] = CShaderResourceView();
}

GeometryBuffer& GeometryBuffer::operator=( GeometryBuffer&& )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	// ���� Ÿ�� ������ ���� �����մϴ�.
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{ };
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = 3;
	HR( pDevice->CreateDescriptorHeap( &heapDesc, IID_PPV_ARGS( &pRTVHeap ) ) );

	// ���� ���ٽ� ������ ���� �����մϴ�.
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	heapDesc.NumDescriptors = 1;
	HR( pDevice->CreateDescriptorHeap( &heapDesc, IID_PPV_ARGS( &pDSVHeap ) ) );

	// �������� ũ�⸦ ��ȸ�մϴ�.
	rtvStride = pDevice->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

	return *this;
}