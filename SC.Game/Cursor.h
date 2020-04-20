#pragma once

namespace SC::Game
{
	/// <summary>
	/// �ۿ��� Ŀ���� �����ϴ� API�� ���� �������̽��� �����մϴ�.
	/// </summary>
	public ref class Cursor abstract sealed
	{
	internal:
		static CursorLockMode mLockMode;
		static int mVisible = true;

	public:
		/// <summary>
		/// Ŀ�� ��� ��带 �����ϰų� �����ɴϴ�.
		/// </summary>
		static property CursorLockMode LockState
		{
			CursorLockMode get();
			void set( CursorLockMode value );
		}

		/// <summary>
		/// Ŀ���� ���̱� ���¸� �����ϰų� �����ɴϴ�.
		/// </summary>
		static property bool Visible
		{
			bool get();
			void set( bool value );
		}
	};
}