using namespace SC;
using namespace SC::Game;
using namespace SC::Game::UI::Shapes;

using namespace std;

using namespace System;

using System::Drawing::RectangleF;

RectangleF Rectangle::OnUpdate( RectangleF clientRect )
{
	auto block = ( tag_ShaderInfo* )mShaderInfoHeap->Map();
	block->output.left = clientRect.X;
	block->output.top = clientRect.Y;
	block->output.width = clientRect.Width;
	block->output.height = clientRect.Height;
	mShaderInfoHeap->Unmap();

	return clientRect;
}

void Rectangle::Render( CDeviceContext& deviceContext )
{
	if ( Fill )
	{
		deviceContext.SetGraphicsRootConstantBufferView( Slot_UI_Brush, Fill->mConstantBuffer->GetGPUVirtualAddress() );
		deviceContext.SetGraphicsRoot32BitConstant( Slot_UI_RenderType, 1 );
		deviceContext.SetGraphicsRootShaderResourceView( Slot_UI_ShaderInfo, mShaderInfoHeap->GetGPUVirtualAddress() );
		deviceContext.DrawInstanced( 4, 1 );
	}
}

Rectangle::Rectangle( String^ xName ) : Shape( xName )
{
	Width = 100;
	Height = 100;

	mShaderInfoHeap = HeapAllocator::Alloc( sizeof( tag_ShaderInfo ) ).Detach();
}

Rectangle::~Rectangle()
{
	this->!Rectangle();
}

Rectangle::!Rectangle()
{
	if ( mShaderInfoHeap )
	{
		ComPtr<IUnknown> p;
		p.Attach( mShaderInfoHeap );
		App::mHeapCommitDCAndGC.GCAdd( move( p ) );

		mShaderInfoHeap = nullptr;
	}
}