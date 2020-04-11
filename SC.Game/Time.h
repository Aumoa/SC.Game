#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� �������� ��� ��ü���� ���Ǵ� Update �� FixedUpdate�� �ð� �帧�� ǥ���մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Time abstract sealed
	{
		static float mDeltaTime;
		static float mFixedDeltaTime;

	public:
		/// <summary>
		/// ���� Update�κ��� ����� �ð��� �� ������ �����ɴϴ�.
		/// </summary>
		static property float DeltaTime
		{
			float get();
		internal:
			void set( float value );
		}

		/// <summary>
		/// ���� FixedUpdate�κ��� ����� �ð��� �� ������ �����ɴϴ�.
		/// </summary>
		static property float FixedDeltaTime
		{
			float get();
		internal:
			void set( float value );
		}
	};
}