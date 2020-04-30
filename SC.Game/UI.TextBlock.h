#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// ������ �ؽ�Ʈ �޽����� ǥ���ϴ� UI ����Դϴ�.
	/// </summary>
	public ref class TextBlock : public Element
	{
		bool mAutoSizing = true;

		TextFormat^ mTextFormat;
		IDWriteTextLayout* mLayout = nullptr;
		GlyphRenderer* mGlyphRenderer = nullptr;

		TextAlignment mTextAlignment = TextAlignment::Left;
		TextVerticalAlignment mTextVerticalAlignment = TextVerticalAlignment::Top;

		System::Drawing::RectangleF mPrevClient;
		System::Drawing::RectangleF mComputed;
		bool mContentChanged = true;

		SC::Mutex* mMutex = nullptr;
		System::String^ mPrevText;

		bool mIsRichText = false;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

	protected:
		/// <summary>
		/// (<see cref="Element"/> Ŭ�������� ��� ��.) ��Ҹ� �����մϴ�.
		/// </summary>
		/// <param name="clientRect"> �θ��� ������ �簢 ������ ���޵˴ϴ�. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	public:
		/// <summary>
		/// <see cref="TextBlock"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü �̸��� �����մϴ�. </param>
		TextBlock( System::String^ xName );
		~TextBlock() override;
		!TextBlock();

		/// <summary>
		/// �ؽ�Ʈ ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property TextFormat^ Format
		{
			TextFormat^ get();
			void set( TextFormat^ value );
		}

		/// <summary>
		/// �ؽ�Ʈ ���� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property TextAlignment Alignment
		{
			TextAlignment get();
			void set( TextAlignment value );
		}

		/// <summary>
		/// �ؽ�Ʈ ���� ���� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property TextVerticalAlignment VerticalAlignment
		{
			TextVerticalAlignment get();
			void set( TextVerticalAlignment value );
		}

		/// <summary>
		/// �ؽ�Ʈ ũ�⿡ ���� ����� ũ�Ⱑ �ڵ����� �����ǵ��� �ϴ� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property bool AutoSizing
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// �ؽ�Ʈ ���θ� ä�� �귯�ø� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Brush^ Fill
		{
			Brush^ get();
			void set( Brush^ value );
		}

		/// <summary>
		/// �ؽ�Ʈ�� ��ü �������� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Opacity
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// �� �ؽ�Ʈ ������ ���� �ִ� �ؽ�Ʈ���� ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property bool IsRichText
		{
			bool get();
			void set( bool value );
		}

	private:
		void OnFormatChanged();
		void OnContentChanged( System::Object^ value );

		void ParseText( System::String^ original );
	};
}