using namespace SC;
using namespace SC::Game;
using namespace SC::Game::UI;

using namespace System;

using System::Drawing::RectangleF;

struct tag
{
	int Type;
	float Opacity;
};

RectangleF Image::OnUpdate( RectangleF clientRect )
{
	auto block = ( tag_ShaderInfo* )mShaderInfoHeap->Map();
	block->input.left = 0;
	block->input.top = 0;
	block->input.width = 1.0f;
	block->input.height = 1.0f;
	block->output.left = clientRect.X;
	block->output.top = clientRect.Y;
	block->output.width = clientRect.Width;
	block->output.height = clientRect.Height;
	mShaderInfoHeap->Unmap();

	return clientRect;
}

void Image::Render( CDeviceContext& deviceContext )
{
	if ( mSource )
	{
		tag tag_RenderType;
		tag_RenderType.Type = 2;
		tag_RenderType.Opacity = mOpacity;

		deviceContext.SetGraphicsRootShaderResource( Slot_UI_Image, *mSource->mShaderResourceView );
		deviceContext.SetGraphicsRoot32BitConstants( Slot_UI_RenderType, 2, &tag_RenderType );
		deviceContext.SetGraphicsRootShaderResourceView( Slot_UI_ShaderInfo, mShaderInfoHeap->GetGPUVirtualAddress() );
		deviceContext.DrawInstanced( 4, 1 );
	}
}

Image::Image( String^ xName ) : Element( xName )
{
	mShaderInfoHeap = HeapAllocator::Alloc( sizeof( tag_ShaderInfo ) ).Detach();
}

Image::~Image()
{
	this->!Image();
}

Image::!Image()
{
	if ( mShaderInfoHeap )
	{
		mShaderInfoHeap->Release();
		mShaderInfoHeap = nullptr;
	}
}

Texture2D^ Image::Source::get()
{
	return mSource;
}

void Image::Source::set( Texture2D^ value )
{
	mSource = value;
}

float Image::Opacity::get()
{
	return mOpacity;
}

void Image::Opacity::set( float value )
{
	mOpacity = value;
}