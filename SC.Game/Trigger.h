#pragma once

namespace SC::Game
{
	/// <summary>
	/// 애니메이션 매개변수로 사용하는 트리거 자료형을 표현합니다.
	/// </summary>
	public value struct Trigger
	{
	private:
		bool mValue;

	public:
		/// <summary> <see cref="Trigger"/>
		/// 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		Trigger( bool initialTrigger )
		{
			mValue = initialTrigger;
		}

		/// <summary>
		/// 현재 상태를 가져오고, 상태가 활성화 상태라면 비활성화 상태로 변경합니다.
		/// </summary>
		bool Action()
		{
			auto ret = mValue;
			mValue = false;
			return ret;
		}

		/// <summary>
		/// 현재 상태를 설정하거나 가져옵니다.
		/// </summary>
		property bool IsActive
		{
			bool get()
			{
				return mValue;
			}

			void set( bool value )
			{
				mValue = value;
			}
		}
	};
}