#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� �������� ��� ��ü���� ���Ǵ� �Է¿� ���� �������̽��� �����մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
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
		/// Ű�� ���� �����ӿ��� ���������� �˻��մϴ�.
		/// </summary>
		/// <param name="keyCode"> �˻��� Ű�ڵ带 �����մϴ�. </param>
		static bool GetKeyDown( KeyCode keyCode );

		/// <summary>
		/// Ű�� ���� �����ӿ��� �������� �˻��մϴ�.
		/// </summary>
		/// <param name="keyCode"> �˻��� Ű�ڵ带 �����մϴ�. </param>
		static bool GetKeyUp( KeyCode keyCode );

		/// <summary>
		/// Ű�� ������ �������� �˻��մϴ�.
		/// </summary>
		/// <param name="keyCode"> �˻��� Ű�ڵ带 �����մϴ�. </param>
		static bool GetKey( KeyCode keyCode );

		/// <summary> 
		/// ���� �����ӿ��� â ��ġ�� �������� �ϴ� �ȼ� ���� Ŀ�� ��ġ�� �����ɴϴ�.
		/// </summary>
		static property System::Drawing::Point MousePosition
		{
			System::Drawing::Point get();
		}

		/// <summary>
		/// ���� �����ӿ��� ��ũ�� �̵����� �����ɴϴ�.
		/// </summary>
		static property System::Drawing::PointF MouseScrollDelta
		{
			System::Drawing::PointF get();
		}
	};
}