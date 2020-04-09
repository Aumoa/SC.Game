#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 폰트, 텍스트 서식 등을 지정하는 텍스트 서식 개체를 표현합니다.
	/// </summary>
	public ref class TextFormat
	{
	internal:
		System::String^ mFontFamilyName;
		float mFontSize = 0;

		IDWriteTextFormat* mTextFormat = nullptr;
		GlyphBuffer* mGlyphBuffer = nullptr;

	public:
		/// <summary>
		/// <see cref="TextFormat"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="fontFamilyName"> 폰트 패밀리 이름을 전달합니다. 빈 텍스트 형식 또는 nullptr 등의 올바르지 않은 텍스트를 전달할 경우 시스템 기본값이 사용됩니다. </param>
		/// <param name="fontSize"> 폰트 크기를 전달합니다. </param>
		TextFormat( System::String^ fontFamilyName, float fontSize );
		~TextFormat();
		!TextFormat();
	};
}