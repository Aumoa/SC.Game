#pragma once

namespace SC::Game
{
	/// <summary>
	/// 앱에서 커서를 관리하는 API에 대한 인터페이스를 제공합니다.
	/// </summary>
	public ref class Cursor abstract sealed
	{
	internal:
		static CursorLockMode mLockMode;
		static int mVisible = true;

	public:
		/// <summary>
		/// 커서 잠금 모드를 설정하거나 가져옵니다.
		/// </summary>
		static property CursorLockMode LockState
		{
			CursorLockMode get();
			void set( CursorLockMode value );
		}

		/// <summary>
		/// 커서의 보이기 상태를 설정하거나 가져옵니다.
		/// </summary>
		static property bool Visible
		{
			bool get();
			void set( bool value );
		}
	};
}