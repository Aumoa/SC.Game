using namespace SC;
using namespace SC::Game::UI;

using namespace std;

Brush::Brush( int type )
{
	mConstantBuffer = HeapAllocator::Alloc( sizeof( Brush_Constants ) ).Detach();

	mConstants = new Brush_Constants{ };
	mConstants->Type = type;
	mConstants->Opacity = 1.0f;

	UpdateBuffer();
}

void Brush::UpdateBuffer()
{
	auto block = ( Brush_Constants* )mConstantBuffer->Map();
	memcpy( block, mConstants, sizeof( *mConstants ) );
	mConstantBuffer->Unmap();
}

Brush::~Brush()
{
	this->!Brush();
}

Brush::!Brush()
{
	if ( mConstantBuffer )
	{
		ComPtr<IUnknown> p;
		p.Attach( mConstantBuffer );
		App::mHeapCommitDCAndGC.GCAdd( move( p ) );
	}

	if ( mConstants )
	{
		delete mConstants;
		mConstants = nullptr;
	}
}

void Brush::Freeze()
{
	mFreezed = true;
}

float Brush::Opacity::get()
{
	return mConstants->Opacity;
}

void Brush::Opacity::set( float value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Brush ��ü�� ����Ǿ����ϴ�. ���� �����ϴ� ���� ���� ���ݿ� �ش��մϴ�." );

	mConstants->Opacity = value;

	UpdateBuffer();
}

bool Brush::IsFreezed::get()
{
	return mFreezed;
}