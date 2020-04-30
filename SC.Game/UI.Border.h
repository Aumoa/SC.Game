#pragma once

namespace SC::Game::UI
{
	ref class Brush;

	/// <summary>
	/// UI 요소에서 경계를 표현합니다.
	/// </summary>
	public ref class Border : public Element
	{
		float mStrokeWidth = 0.0f;
		Thickness mPadding = Thickness( 0 );

		Brush^ mBrush;
		Heap* mHeap = nullptr;

	protected:
		/// <summary>
		/// (<see cref="Panel"/> 클래스에서 상속 됨.) 요소를 갱신합니다. 
		/// </summary>
		/// <param name="clientRect"> 부모의 컨텐츠 사각 영역이 전달됩니다. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

	public:
		~Border();
		!Border();

		/// <summary>
		/// <see cref="Border"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체 이름을 전달합니다. </param>
		Border( System::String^ xName );

		/// <summary>
		/// 경계 선분의 굵기를 설정하거나 가져옵니다.
		/// </summary>
		property float StrokeWidth
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 경계 내부의 여백 크기를 설정하거나 가져옵니다.
		/// </summary>
		property Thickness Padding
		{
			Thickness get();
			void set( Thickness value );
		}

		/// <summary>
		/// 경개 선분을 칠할 브러시를 설정하거나 가져옵니다.
		/// </summary>
		property Brush^ Fill
		{
			Brush^ get();
			void set( Brush^ value );
		}
	};
}