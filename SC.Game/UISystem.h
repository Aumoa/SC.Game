#pragma once

namespace SC::Game::UI
{
	ref class Page;
	ref class SolidColorBrush;
	ref class TextFormat;
}

namespace SC::Game
{
	class UISystem abstract
	{
		struct Constants
		{
			float Width;
			float Height;
		};

	public:
		static CDeviceContext mDeviceContext;
		static gcroot<UI::Page^> mRootPage;
		static gcroot<UI::Page^> mRemovedPages[2];
		static gcroot<UI::Page^> mReservedPage;
		static gcroot<UI::SolidColorBrush^> mDefaultBlackBrush;
		static gcroot<UI::TextFormat^> mDefaultTextFormat;

		static float mWidth;
		static float mHeight;

		static ComPtr<Heap> mConstantBuffer;
		static D3D12_VIEWPORT mViewport;
		static D3D12_RECT mScissorRect;
		static ComPtr<LargeHeap> mShaderDispatchInfo;
		static UINT mShaderDispatchInfoIndex;

		static std::set<GlyphBuffer*> mGlyphBuffers;
		static Mutex mMutex;
		static bool mDisposed;

	public:
		static void Initialize();
		
		static void Update( int frameIndex );
		static void Render( int frameIndex );

	private:
		static void OnDisposing();
		static void OnResizing( int width, int height );
	};
}