#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// ��Ʈ, �ؽ�Ʈ ���� ���� �����ϴ� �ؽ�Ʈ ���� ��ü�� ǥ���մϴ�.
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
		/// <see cref="TextFormat"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="fontFamilyName"> ��Ʈ �йи� �̸��� �����մϴ�. �� �ؽ�Ʈ ���� �Ǵ� nullptr ���� �ùٸ��� ���� �ؽ�Ʈ�� ������ ��� �ý��� �⺻���� ���˴ϴ�. </param>
		/// <param name="fontSize"> ��Ʈ ũ�⸦ �����մϴ�. </param>
		TextFormat( System::String^ fontFamilyName, float fontSize );
		~TextFormat();
		!TextFormat();
	};
}