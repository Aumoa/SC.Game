using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;

using namespace std;
using namespace std::filesystem;

void Texture2D::InitializeFrom( IWICBitmapDecoder* pDecoder, TextureFormat format )
{
	auto pWICImagingFactory = Graphics::mFactory->pWICFactory.Get();
	auto pDevice = Graphics::mDevice->pDevice.Get();
	ComPtr<IWICBitmapFrameDecode> pFrame;
	ComPtr<IWICFormatConverter> pConverter;

	GUID wicPixelFormat;
	DXGI_FORMAT dxgiPixelFormat;

	switch ( format )
	{
	case TextureFormat::PRGBA_32bpp:
		wicPixelFormat = GUID_WICPixelFormat32bppPRGBA;
		dxgiPixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		break;
	case TextureFormat::Gray_8bpp:
		wicPixelFormat = GUID_WICPixelFormat8bppGray;
		dxgiPixelFormat = DXGI_FORMAT_R8_UNORM;
		break;
	default:
		throw gcnew ArgumentException();
	}

	// �̹����� 0�� �������� ���ɴϴ�.
	HR( pDecoder->GetFrame( 0, &pFrame ) );

	// ������ ��ü�� ������ �̹����� ������ ��ȯ�մϴ�.
	HR( pWICImagingFactory->CreateFormatConverter( &pConverter ) );
	HR( pConverter->Initialize( pFrame.Get(), wicPixelFormat, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom ) );

	// �̹����� ũ�⸦ ��ȸ�մϴ�.
	UINT width, height;
	HR( pConverter->GetSize( &width, &height ) );

	// �ؽ�ó ������ �����մϴ�.
	D3D12_RESOURCE_DESC textureDesc{ };
	textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.DepthOrArraySize = 1;
	textureDesc.MipLevels = 1;
	textureDesc.Format = dxgiPixelFormat;
	textureDesc.SampleDesc = { 1, 0 };

	// �ؽ�ó ������ ������� ������ ũ�⸦ ��ȸ�մϴ�.
	UINT64 totalSizeInBytes;
	D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
	pDevice->GetCopyableFootprints( &textureDesc, 0, 1, 0, &layout, nullptr, nullptr, &totalSizeInBytes );

	// ���� ������ �����մϴ�.
	D3D12_RESOURCE_DESC bufferDesc{ };
	bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	bufferDesc.Width = totalSizeInBytes;
	bufferDesc.Height = 1;
	bufferDesc.DepthOrArraySize = 1;
	bufferDesc.MipLevels = 1;
	bufferDesc.SampleDesc = { 1, 0 };
	bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���ε� �� �ڿ��� �����մϴ�.
	ComPtr<ID3D12Resource> pUploadHeap;
	D3D12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_UPLOAD };
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS( &pUploadHeap ) ) );

	// ���� �ؽ�ó �ڿ��� �����մϴ�.
	ComPtr<ID3D12Resource> pTexture2D;
	heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	HR( pDevice->CreateCommittedResource( &heapProp, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS( &pTexture2D ) ) );

	// ���ε� ���� �ؽ�ó �����͸� �����մϴ�.
	void* pBlock = nullptr;
	HR( pUploadHeap->Map( 0, nullptr, &pBlock ) );
	HR( pConverter->CopyPixels( nullptr, ( UINT )layout.Footprint.RowPitch, ( UINT )totalSizeInBytes, ( BYTE* )pBlock ) );
	pUploadHeap->Unmap( 0, nullptr );

	// �ؽ�ó ���� ��� �Ҵ��� ���� ��� �Ҵ�⸦ �غ��մϴ�.
	CDeviceContext deviceContext( D3D12_COMMAND_LIST_TYPE_COPY, true );
	deviceContext.Reset( 0 );

	D3D12_TEXTURE_COPY_LOCATION dst{ };
	auto src = dst;

	// ���� ��� ���� ������ �����մϴ�.
	dst.pResource = pTexture2D.Get();
	dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
	dst.SubresourceIndex = 0;

	// ���� ���� ���� ������ �����մϴ�.
	src.pResource = pUploadHeap.Get();
	src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
	src.PlacedFootprint = layout;

	// ���� ����� �߰��մϴ�.
	deviceContext.CopyTextureRegion( &dst, 0, 0, 0, &src, nullptr );

	// ��� ����� �ݰ� ����� ī�� ť�� �����մϴ�.
	auto& copyQueue = Graphics::mCopyQueue;
	deviceContext.Close();

	copyQueue->Execute( deviceContext );
	UINT64 fenceValue = copyQueue->Signal();

	// ���̴� �ڿ� �����ڸ� �����մϴ�.
	mShaderResourceView = new CShaderResourceView( DescriptorAllocator::CreateShaderResourceView( pTexture2D.Get(), nullptr ) );

	HEvent hevent;
	copyQueue->SetEventOnCompletion( fenceValue, hevent );
	hevent.WaitForSingleObject();

#if defined( _DEBUG )
	pTexture2D->SetName( L"Texture2D.pTexture2D" );
#endif

	mWidth = width;
	mHeight = height;
	mTexture2D = pTexture2D.Detach();
}

Texture2D::~Texture2D()
{
	this->!Texture2D();
}

Texture2D::!Texture2D()
{
	if ( mTexture2D )
	{
		mTexture2D->Release();
		mTexture2D = nullptr;
	}

	if ( !App::mDisposed )
	{
		if ( mShaderResourceView )
		{
			delete mShaderResourceView;
			mShaderResourceView = nullptr;
		}
	}
}

Texture2D::Texture2D( String^ xName, String^ filepath, TextureFormat format ) : Asset( xName )
{
	auto pImagingFactory = Graphics::mFactory->pWICFactory.Get();
	ComPtr<IWICBitmapDecoder> pDecoder;

	// ���� �����͸� ������� �̹��� ���ڴ��� �����մϴ�.
	HR( pImagingFactory->CreateDecoderFromFilename( msclr::interop::marshal_context().marshal_as<const wchar_t*>( filepath ), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder ) );

	// ���ڴ� ��ü�� �̿��Ͽ� �̹��� ��ü�� �ʱ�ȭ�մϴ�.
	InitializeFrom( pDecoder.Get(), format );

	mFilename = xName;
}

Texture2D::Texture2D( String^ xName, cli::array<Byte>^ textureData, UInt32 sizeInBytes, TextureFormat format ) : Asset( xName )
{
	auto pImagingFactory = Graphics::mFactory->pWICFactory.Get();

	ComPtr<IWICStream> pStream;
	ComPtr<IWICBitmapDecoder> pDecoder;

	// ��Ʈ���� ���� �޸� �����͸� �ҷ��ɴϴ�.
	pin_ptr<Byte> ptr = &textureData[0];
	HR( pImagingFactory->CreateStream( &pStream ) );
	HR( pStream->InitializeFromMemory( ( WICInProcPointer )ptr, sizeInBytes ) );

	// ��Ʈ�� �����͸� ������� �̹��� ���ڴ��� �����մϴ�.
	HR( pImagingFactory->CreateDecoderFromStream( pStream.Get(), nullptr, WICDecodeMetadataCacheOnLoad, &pDecoder ) );

	// ���ڴ� ��ü�� �̿��Ͽ� �̹��� ��ü�� �ʱ�ȭ�մϴ�.
	InitializeFrom( pDecoder.Get(), format );

	mFilename = "<Raw>";
}

String^ Texture2D::ToString()
{
	return String::Format(
		"{0} ({1})",
		Asset::ToString(),
		mFilename
	);
}

UInt32 Texture2D::Width::get()
{
	return mWidth;
}

UInt32 Texture2D::Height::get()
{
	return mHeight;
}