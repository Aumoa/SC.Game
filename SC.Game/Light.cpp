using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Drawing;
using namespace System::Numerics;

void Light::InitializeDepthBuffer()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_DEFAULT };

	D3D12_RESOURCE_DESC textureDesc{ };
	textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureDesc.Width = ( UINT64 )mShadowResolution.Width;
	textureDesc.Height = ( UINT )mShadowResolution.Height;
	textureDesc.DepthOrArraySize = 1;
	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc = { 1, 0 };
	textureDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	textureDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE depthClear{ DXGI_FORMAT_D32_FLOAT };
	depthClear.DepthStencil.Depth = 1.0f;

	ComPtr<ID3D12Resource> pShadowDepthMap;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &depthClear, IID_PPV_ARGS( &pShadowDepthMap ) ) );

	ComPtr<ID3D12DescriptorHeap> pDSVHeap;
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{ };
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	heapDesc.NumDescriptors = 1;
	HR( pDevice->CreateDescriptorHeap( &heapDesc, IID_PPV_ARGS( &pDSVHeap ) ) );

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{ };
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;

	pDevice->CreateDepthStencilView( pShadowDepthMap.Get(), &dsvDesc, pDSVHeap->GetCPUDescriptorHandleForHeapStart() );

	if ( mShadowMap )
	{
		mShadowMap->Release();
		mShadowMap = nullptr;
	}

	if ( mDSVHeap )
	{
		mDSVHeap->Release();
		mDSVHeap = nullptr;
	}

	if ( mShaderResourceView )
	{
		delete mShaderResourceView;
		mShaderResourceView = nullptr;
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC srv{ };
	srv.Format = DXGI_FORMAT_R32_FLOAT;
	srv.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srv.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srv.Texture2D.MipLevels = 1;

	mShadowMap = pShadowDepthMap.Detach();
	mDSVHeap = pDSVHeap.Detach();
	mShaderResourceView = new CShaderResourceView( DescriptorAllocator::CreateShaderResourceView( mShadowMap, &srv ) );
}

void Light::UpdateBuffer()
{
	if ( Transform->IsUpdated || mFrameUpdated )
	{
		auto rot = Transform->Rotation;

		auto eye = Transform->Position;
		auto dir = Vector3::Transform( Vector3::UnitZ, rot );
		auto up = Vector3::Transform( Vector3::UnitY, rot );

		auto view = LookToLH( eye, dir, up );
		auto proj = OrthographicLH( mWidth, mHeight, 0.1f, 1000.0f );
		Assign( mFrameResource->Direction, dir );

		auto vp = Matrix4x4::Multiply( view, proj );
		Assign( mFrameResource->ViewProj, vp );

		auto block = mConstantBuffer->Map();
		memcpy( block, mFrameResource, sizeof( *mFrameResource ) );
		mConstantBuffer->Unmap();

		mFrameUpdated = false;
	}
}

void Light::BeginDraw( CDeviceContext& deviceContext )
{
	if ( mShadowMap && mDSVHeap )
	{
		auto dsvHandle = mDSVHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_VIEWPORT viewport{ };
		D3D12_RECT scissor{ };

		viewport.Width = ( float )mShadowResolution.Width;
		viewport.Height = ( float )mShadowResolution.Height;
		viewport.MaxDepth = 1.0f;

		scissor.right = mShadowResolution.Width;
		scissor.bottom = mShadowResolution.Height;

		deviceContext.OMSetRenderTargets( 0, nullptr, FALSE, &dsvHandle );
		deviceContext.RSSetViewports( 1, &viewport );
		deviceContext.RSSetScissorRects( 1, &scissor );

		deviceContext.TransitionBarrier( mShadowMap, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_DEPTH_WRITE, 0 );
		deviceContext.ClearDepthStencilView( dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr );
	}
}

void Light::EndDraw( CDeviceContext& deviceContext )
{
	if ( mShadowMap && mDSVHeap )
	{
		deviceContext.TransitionBarrier( mShadowMap, D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, 0 );
	}
}

Light::Light()
{
	mShadowResolution = Size( 2048, 2048 );

	mConstantBuffer = HeapAllocator::Alloc( sizeof( Light_Constants ) ).Detach();
	mFrameResource = new Light_Constants{ };

	Color = System::Drawing::Color::White;
	Diffuse = 1.0f;
}

Light::~Light()
{
	this->!Light();
}

Light::!Light()
{
	if ( mConstantBuffer )
	{
		mConstantBuffer->Release();
		mConstantBuffer = nullptr;
	}

	if ( mFrameResource )
	{
		delete mFrameResource;
		mFrameResource = nullptr;
	}

	if ( mShaderResourceView )
	{
		delete mShaderResourceView;
		mShaderResourceView = nullptr;
	}
}

Object^ Light::Clone()
{
	auto clone = gcnew Light();
	*clone->mFrameResource = *mFrameResource;
	return clone;
}

Color Light::Color::get()
{
	System::Drawing::Color color;
	Assign( color, mFrameResource->Color );
	return color;
}

void Light::Color::set( System::Drawing::Color value )
{
	Assign( mFrameResource->Color, value );
	mFrameUpdated = true;
}

float Light::Ambient::get()
{
	return mFrameResource->Ambient;
}

void Light::Ambient::set( float value )
{
	mFrameResource->Ambient = value;
	mFrameUpdated = true;
}

float Light::Diffuse::get()
{
	return mFrameResource->Diffuse;
}

void Light::Diffuse::set( float value )
{
	mFrameResource->Diffuse = value;
	mFrameUpdated = true;
}

float Light::Specular::get()
{
	return mFrameResource->Specular;
}

void Light::Specular::set( float value )
{
	mFrameResource->Specular = value;
	mFrameUpdated = true;
}

bool Light::IsShadowCast::get()
{
	return ( bool )mFrameResource->ShadowCast;
}

void Light::IsShadowCast::set( bool value )
{
	mFrameUpdated = true;

	if ( !mFrameResource->ShadowCast && value )
	{
		InitializeDepthBuffer();
	}
	mFrameResource->ShadowCast = value;
}

Size Light::ShadowResolution::get()
{
	return mShadowResolution;
}

void Light::ShadowResolution::set( Size value )
{
	mShadowResolution = value;
	if ( mFrameResource->ShadowCast )
		InitializeDepthBuffer();
}

float Light::Width::get()
{
	return mWidth;
}

void Light::Width::set( float value )
{
	mWidth = value;

	mFrameUpdated = true;
}

float Light::Height::get()
{
	return mHeight;
}

void Light::Height::set( float value )
{
	mHeight = value;

	mFrameUpdated = true;
}