#pragma once

namespace SC::Game::UI::Shapes
{
	/// <summary>
	/// 사각형 모양을 표현하는 UI 요소입니다.
	/// </summary>
	public ref class Rectangle : public Shape
	{
		Heap* mShaderInfoHeap = nullptr;

	protected:
		/// <summary>
		/// (<see cref="Element"/> 클래스에서 상속 됨.) 요소를 갱신합니다.
		/// </summary>
		/// <param name="clientRect"> 부모의 컨텐츠 사각 영역이 전달됩니다. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

	public:
		/// <summary>
		/// <see cref="Rectangle"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체 이름을 전달합니다. </param>
		Rectangle( System::String^ xName );
		~Rectangle();
		!Rectangle();
	};
}