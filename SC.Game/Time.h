#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� �������� ��� ��ü���� ���Ǵ� Update �� FixedUpdate�� �ð� �帧�� ǥ���մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Time abstract sealed
	{
		static double mDeltaTime;
		static double mFixedDeltaTime;

	public:
		/// <summary>
		/// ���� Update�κ��� ����� �ð��� �� ������ �����ɴϴ�.
		/// </summary>
		static property double DeltaTime
		{
			double get();
		internal:
			void set( double value );
		}

		/// <summary>
		/// ���� FixedUpdate�κ��� ����� �ð��� �� ������ �����ɴϴ�.
		/// </summary>
		static property double FixedDeltaTime
		{
			double get();
		internal:
			void set( double value );
		}
	};
}