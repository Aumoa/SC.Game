#pragma once

namespace SC::Game::UI
{
	ref class Brush;

	class RichTextColorUnknown : public IUnknown
	{
		ULONG64 mRefCount = 0;

	public:
		gcroot<Brush^> mBrush;

	public:
		RichTextColorUnknown( Brush^ brush );

		ULONG STDMETHODCALLTYPE AddRef() override;
		ULONG STDMETHODCALLTYPE Release() override;
		HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** ppvObject ) override;
	};
}