#pragma once

namespace SC::Game::UI::Shapes
{
	/// <summary>
	/// 모양을 표현하는 UI 요소 형식 계층 구조의 루트입니다.
	/// </summary>
	public ref class Shape : public Element
	{
		Brush^ mBrush;

	internal:
		Shape( System::String^ xName );

	public:
		/// <summary>
		/// 모양의 채우기 브러시를 설정하거나 가져옵니다.
		/// </summary>
		property Brush^ Fill
		{
			Brush^ get();
			void set( Brush^ value );
		}
	};
}