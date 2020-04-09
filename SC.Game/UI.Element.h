#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 요소의 컨텐츠가 변경되었을 경우 발생하는 이벤트의 대리자 형식입니다.
	/// </summary>
	public delegate void ContentChangedDelegate( System::Object^ content );

	/// <summary>
	/// UI 요소 형식 계층 구조의 루트입니다. 파생 클래스에 UI 기본 기능을 제공합니다.
	/// </summary>
	public ref class Element : public DependencyObject
	{
		System::String^ mName;
		float mWidth;
		float mHeight;
		System::Object^ mContent;
		Thickness mMargin;
		Anchor mAnchor;
		System::Drawing::RectangleF mActualRenderingRect;

	protected:
		/// <summary>
		/// <see cref="Element"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체의 참조 이름을 전달합니다. </param>
		Element( System::String^ xName );

		/// <summary>
		/// 요소가 갱신될 때 호출되는 함수입니다.
		/// </summary>
		/// <param name="clientRect"> 부모 요소의 컨텐츠 렌더링 영역이 전달됩니다. </param>
		/// <returns> 해당 요소의 실제 렌더링 영역을 반환합니다. </returns>
		virtual System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect );

	internal:
		virtual void Render( CDeviceContext& deviceContext );

	public:
		/// <summary>
		/// (<see cref="Object"/> 클래스에서 상속 됨.) 개체의 요약 정보를 텍스트 형식으로 반환합니다.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// UI 요소를 업데이트합니다.
		/// </summary>
		/// <param name="clientRect"> 이 요소의 업데이트를 호출한 UI 레이아웃의 클라이언트 영역을 전달합니다. </param>
		virtual void Update( System::Drawing::RectangleF clientRect );

		/// <summary>
		/// 요소의 여백 두께를 설정하거나 가져옵니다.
		/// </summary>
		property Thickness Margin
		{
			Thickness get();
			void set( Thickness value );
		}

		/// <summary>
		/// 요소의 참조 이름을 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}

		/// <summary>
		/// UI 컨텐츠 요소를 설정하거나 가져옵니다.
		/// </summary>
		property System::Object^ Content
		{
			System::Object^ get();
			void set( System::Object^ value );
		}

		/// <summary>
		/// 요소의 너비를 설정하거나 가져옵니다.
		/// </summary>
		property float Width
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 요소의 높이를 설정하거나 가져옵니다.
		/// </summary>
		property float Height
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 요소의 고정점을 설정하거나 가져옵니다.
		/// </summary>
		property UI::Anchor Anchor
		{
			UI::Anchor get();
			void set( UI::Anchor value );
		}

		/// <summary>
		/// 요소의 실제 렌더링 영역을 가져옵니다.
		/// </summary>
		property System::Drawing::RectangleF ActualRenderingRect
		{
			System::Drawing::RectangleF get();
		}

		/// <summary>
		/// 요소의 컨텐츠 개체가 변경되었을 경우 발생하는 이벤트입니다.
		/// </summary>
		event ContentChangedDelegate^ ContentChanged;
	};
}