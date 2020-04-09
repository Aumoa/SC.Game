using namespace SC;
using namespace SC::Game::UI;

RichTextColorUnknown::RichTextColorUnknown( Brush^ brush )
{
	mBrush = brush;
}

#pragma unmanaged
ULONG STDMETHODCALLTYPE RichTextColorUnknown::AddRef()
{
	return ( ULONG )InterlockedIncrement64( ( volatile LONG64* )&mRefCount );
}

ULONG STDMETHODCALLTYPE RichTextColorUnknown::Release()
{
	auto r = InterlockedDecrement64( ( volatile LONG64* )&mRefCount );
	if ( r == 0 )
	{
		delete this;
		return 0;
	}
	else
	{
		return ( ULONG )r;
	}
}

HRESULT STDMETHODCALLTYPE RichTextColorUnknown::QueryInterface( REFIID riid, void** ppvObject )
{
	if ( riid == __uuidof( IUnknown ) )
	{
		*ppvObject = dynamic_cast< IUnknown* >( this );
		AddRef();
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}