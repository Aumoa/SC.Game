#pragma once

namespace SC::Game
{
	struct tag_GlyphInfo
	{
		UINT16 glyphIndex;
		IDWriteFontFace* pFontFace;
		float offsetX;
		float width;

		constexpr bool operator==( const tag_GlyphInfo& right ) const
		{
			return glyphIndex == right.glyphIndex
				&& pFontFace == right.pFontFace;
		}
	};

	struct tag_GlyphRunCache
	{
		int CacheVersion = -1;
		std::vector<tag_ShaderInfo> CacheData;
	};
}

namespace std
{
	template<> class hash<SC::Game::tag_GlyphInfo>
	{
		inline static hash<UINT16> u16Hash;

	public:
		size_t operator() ( const SC::Game::tag_GlyphInfo& right ) const
		{
			return u16Hash( right.glyphIndex ) ^ ( size_t )right.pFontFace;
		}
	};
}

namespace SC::Game
{
	class GlyphBuffer
	{
	public:
		static constexpr const DXGI_FORMAT Format = DXGI_FORMAT_A8_UNORM;
		static constexpr const float padding = 2.0f;

		ComPtr<IDWriteTextFormat> pTextFormat;
		ComPtr<IDWriteFont> pFont;
		CDeviceContext mDeviceContext;
		ComPtr<ID2D1SolidColorBrush> pAlpha1Brush;
		float fontEmSize = 0;

		UINT maxWidth = 0;
		float maxHeight = 0;
		UINT maxHeightAligned = 0;
		float ascent = 0;
		float descent = 0;

		ComPtr<ID3D12Resource> pGlyphTexture;
		ComPtr<ID3D11Resource> pGlyphTextureInterop;
		ComPtr<ID2D1Bitmap1> pGlyphBitmap;
		CShaderResourceView mShaderResourceView;
		float lastGlyphOffset = 0;

		std::unordered_map<tag_GlyphInfo, float> allocated;
		std::unordered_set<tag_GlyphInfo> locked;
		float lockedWidth = 0;
		std::unordered_set<tag_GlyphInfo> added;
		float appendWidth = 0;

		UINT64 lastPending = 0;
		Mutex glyphLocking;

	public:
		GlyphBuffer( const std::wstring_view& fontFamilyName, float fontSize );
		~GlyphBuffer();

		void Restart();
		void PushGlyphRun( const DWRITE_GLYPH_RUN* glyphRun );
		void LockGlyphs();
		void DrawGlyphRun( CDeviceContext* clientDrawingContext, float baselineX, float baselineY, const DWRITE_GLYPH_RUN* glyphRun );

		float designUnitsPerEm = 0;
		float designSize = 0;

	private:
		void Expand();
	};
}