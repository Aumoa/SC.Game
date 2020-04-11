#pragma once

namespace SC::Game
{
	/// <summary>
	/// 현재 실행중인 장면 개체에서 사용되는 Update 및 FixedUpdate의 시간 흐름을 표현합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class Time abstract sealed
	{
		static float mDeltaTime;
		static float mFixedDeltaTime;

	public:
		/// <summary>
		/// 이전 Update로부터 경과된 시간을 초 단위로 가져옵니다.
		/// </summary>
		static property float DeltaTime
		{
			float get();
		internal:
			void set( float value );
		}

		/// <summary>
		/// 이전 FixedUpdate로부터 경과된 시간을 초 단위로 가져옵니다.
		/// </summary>
		static property float FixedDeltaTime
		{
			float get();
		internal:
			void set( float value );
		}
	};
}