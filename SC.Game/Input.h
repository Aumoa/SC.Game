#pragma once

namespace SC::Game
{
	/// <summary>
	/// 현재 실행중인 장면 개체에서 사용되는 입력에 대한 인터페이스를 제공합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class Input abstract sealed
	{
	internal:
		static System::Drawing::Point mCursorPos;
		static System::Drawing::PointF mScrollDelta;

		static array<bool, 1>^ mPrevKeyboardData;
		static array<bool, 1>^ mKeyboardData;

	internal:
		static void Update();

	public:
		static Input();

		/// <summary>
		/// 키가 현재 프레임에서 눌러졌는지 검사합니다.
		/// </summary>
		/// <param name="keyCode"> 검사할 키코드를 전달합니다. </param>
		static bool GetKeyDown( KeyCode keyCode );

		/// <summary>
		/// 키가 현재 프레임에서 놓였는지 검사합니다.
		/// </summary>
		/// <param name="keyCode"> 검사할 키코드를 전달합니다. </param>
		static bool GetKeyUp( KeyCode keyCode );

		/// <summary>
		/// 키가 눌러짐 상태인지 검사합니다.
		/// </summary>
		/// <param name="keyCode"> 검사할 키코드를 전달합니다. </param>
		static bool GetKey( KeyCode keyCode );

		/// <summary> 
		/// 현재 프레임에서 창 위치를 기준으로 하는 픽셀 단위 커서 위치를 가져옵니다.
		/// </summary>
		static property System::Drawing::Point MousePosition
		{
			System::Drawing::Point get();
		}

		/// <summary>
		/// 현재 프레임에서 스크롤 이동량을 가져옵니다.
		/// </summary>
		static property System::Drawing::PointF MouseScrollDelta
		{
			System::Drawing::PointF get();
		}
	};
}