using namespace SC;
using namespace SC::Game::UI;

using namespace System;

TextFormat::TextFormat( String^ fontFamilyName, float fontSize )
{
	std::wstring wstr = msclr::interop::marshal_context().marshal_as<const wchar_t*>( fontFamilyName );

	ComPtr<IDWriteTextFormat> pTextFormat;
	HR( Graphics::mFactory->pDWriteFactory->CreateTextFormat( wstr.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ko-KR", &pTextFormat ) );
	mTextFormat = pTextFormat.Detach();

	mGlyphBuffer = new GlyphBuffer( wstr, fontSize );
}

TextFormat::~TextFormat()
{
	this->!TextFormat();
}

TextFormat::!TextFormat()
{
	if ( !App::mDisposed )
	{
		if ( mTextFormat )
		{
			mTextFormat->Release();
			mTextFormat = nullptr;
		}

		if ( mGlyphBuffer )
		{
			delete mGlyphBuffer;
			mGlyphBuffer = nullptr;
		}
	}
}