#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 고정된 텍스트 메시지를 표시하는 UI 요소입니다.
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
		/// (<see cref="Element"/> 클래스에서 상속 됨.) 요소를 갱신합니다.
		/// </summary>
		/// <param name="clientRect"> 부모의 컨텐츠 사각 영역이 전달됩니다. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	public:
		/// <summary>
		/// <see cref="TextBlock"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체 이름을 전달합니다. </param>
		TextBlock( System::String^ xName );
		~TextBlock() override;
		!TextBlock();

		/// <summary>
		/// 텍스트 서식을 설정하거나 가져옵니다.
		/// </summary>
		property TextFormat^ Format
		{
			TextFormat^ get();
			void set( TextFormat^ value );
		}

		/// <summary>
		/// 텍스트 정렬 형식을 설정하거나 가져옵니다.
		/// </summary>
		property TextAlignment Alignment
		{
			TextAlignment get();
			void set( TextAlignment value );
		}

		/// <summary>
		/// 텍스트 수직 정렬 형식을 설정하거나 가져옵니다.
		/// </summary>
		property TextVerticalAlignment VerticalAlignment
		{
			TextVerticalAlignment get();
			void set( TextVerticalAlignment value );
		}

		/// <summary>
		/// 텍스트 크기에 맞춰 요소의 크기가 자동으로 설정되도록 하는 값을 설정하거나 가져옵니다.
		/// </summary>
		property bool AutoSizing
		{
			bool get();
			void set( bool value );
		}

		/// <summary>
		/// 텍스트 내부를 채울 브러시를 설정하거나 가져옵니다.
		/// </summary>
		property Brush^ Fill
		{
			Brush^ get();
			void set( Brush^ value );
		}

		/// <summary>
		/// 텍스트의 전체 불투명도를 설정하거나 가져옵니다.
		/// </summary>
		property float Opacity
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 이 텍스트 형식이 서식 있는 텍스트임을 나타내는 값을 설정하거나 가져옵니다.
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