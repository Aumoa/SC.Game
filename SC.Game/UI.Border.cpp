using namespace SC;
using namespace SC::Game::UI;

using namespace System;
using namespace System::Drawing;

using namespace std;

RectangleF Border::OnUpdate( RectangleF clientRect )
{
	// Align in pixels.
	clientRect.X = ( float )( int )clientRect.Left;
	clientRect.Y = ( float )( int )clientRect.Top;
	clientRect.Width = ( float )( int )( clientRect.Width + 0.5f );
	clientRect.Height = ( float )( int )( clientRect.Height + 0.5f );

	auto contentRect = clientRect;
	contentRect.X += mPadding.Left;
	contentRect.Y += mPadding.Top;
	contentRect.Width -= mPadding.Left + mPadding.Right;
	contentRect.Height -= mPadding.Top + mPadding.Bottom;

	if ( Content && Element::typeid->IsAssignableFrom( Content->GetType() ) )
	{
		auto item = ( Element^ )Content;
		item->Update( contentRect );
		contentRect = item->ActualRenderingRect;
	}

	clientRect.X = ( float )( int )( contentRect.Left - mPadding.Left );
	clientRect.Y = ( float )( int )( contentRect.Top - mPadding.Top );
	clientRect.Width = ( float )( int )( contentRect.Width + mPadding.Left + mPadding.Right + 0.5 );
	clientRect.Height = ( float )( int )( contentRect.Height + mPadding.Top + mPadding.Bottom + 0.5 );

	auto shaderInfos = ( tag_ShaderInfo* )mHeap->Map();

	/* top line */
	shaderInfos[0].output.left = clientRect.Left;
	shaderInfos[0].output.top = clientRect.Top;
	shaderInfos[0].output.width = clientRect.Width;
	shaderInfos[0].output.height = mStrokeWidth;

	/* left line */
	shaderInfos[1].output.left = clientRect.Left;
	shaderInfos[1].output.top = clientRect.Top;
	shaderInfos[1].output.width = mStrokeWidth;
	shaderInfos[1].output.height = clientRect.Height;

	/* bottom line */
	shaderInfos[2].output.left = clientRect.Left;
	shaderInfos[2].output.top = clientRect.Bottom - mStrokeWidth;
	shaderInfos[2].output.width = clientRect.Width;
	shaderInfos[2].output.height = mStrokeWidth;

	/* right line */
	shaderInfos[3].output.left = clientRect.Right - mStrokeWidth;
	shaderInfos[3].output.top = clientRect.Top;
	shaderInfos[3].output.width = mStrokeWidth;
	shaderInfos[3].output.height = clientRect.Height;

	mHeap->Unmap();

	return clientRect;
}

void Border::Render( CDeviceContext& deviceContext )
{
	auto contentRect = ActualRenderingRect;

	if ( mStrokeWidth >= 0.01f )
	{
		deviceContext.SetGraphicsRootConstantBufferView( Slot_UI_Brush, Fill->mConstantBuffer->GetGPUVirtualAddress() );
		deviceContext.SetGraphicsRoot32BitConstant( Slot_UI_RenderType, 1 );

		deviceContext.SetGraphicsRootShaderResourceView( Slot_UI_ShaderInfo, mHeap->GetGPUVirtualAddress() );
		deviceContext.DrawInstanced( 4, 4 );
	}

	if ( Content && Element::typeid->IsAssignableFrom( Content->GetType() ) )
	{
		auto item = ( Element^ )Content;
		item->Render( deviceContext );
	}
}

Border::~Border()
{
	this->!Border();
}

Border::!Border()
{
	if ( mHeap )
	{
		mHeap->Release();
		mHeap = nullptr;
	}
}

Border::Border( String^ xName ) : Element( xName )
{
	mHeap = HeapAllocator::Alloc( sizeof( tag_ShaderInfo ) * 4 ).Detach();
	Fill = UISystem::mDefaultBlackBrush;
	StrokeWidth = 1.0f;
}

float Border::StrokeWidth::get()
{
	return mStrokeWidth;
}

void Border::StrokeWidth::set( float value )
{
	mStrokeWidth = value;
}

Thickness Border::Padding::get()
{
	return mPadding;
}

void Border::Padding::set( Thickness value )
{
	mPadding = value;
}

SC::Game::UI::Brush^ Border::Fill::get()
{
	return mBrush;
}

void Border::Fill::set( SC::Game::UI::Brush^ value )
{
	mBrush = value;
}