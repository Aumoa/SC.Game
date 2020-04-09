using System;
using System.Runtime.InteropServices;
using System.Text;

namespace SC.Diagnostics
{
	/// <summary>
	/// <see cref="StepTimer"/> 클래스에서 역참조하는 대리자 형식을 정의합니다.
	/// </summary>
	public delegate void StepTimerCallbackDelegate();

	/// <summary>
	/// 경과 시간 및 시물레이션 타이밍을 측정하는 데 사용되는 고해상도 타이머 기능을 제공합니다.
	/// </summary>
	public class StepTimer
	{
		static readonly ulong frequency = 1000000000;

		ulong standard = 0;

		ulong lasttime = 0;
		ulong maxDelta = 0;

		ulong elapsedTicks = 0;
		ulong totalTicks = 0;
		ulong leftOverTicks = 0;

		uint frameCount = 0;
		uint framesPerSecond = 0;
		uint framesThisSecond = 0;
		ulong secondCounter = 0;

		bool isFixedTimeStep = false;
		ulong targetElapsedTicks = 0;

		/// <summary>
		/// <see cref="StepTimer"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		public StepTimer()
		{
			standard = QueryPerformanceCounter();
		}

		/// <summary>
		/// (<see cref="Object"/> 클래스에서 상속 됨.) 경과 시간 및 초당 프레임 횟수를 텍스트 형식으로 가져옵니다.
		/// </summary>
		public override string ToString()
		{
			int length = ( int )TotalSeconds;
			bool under = false;
			StringBuilder builder = new StringBuilder();

			if ( length >= 3600 )
			{
				builder.Append( length / 3600 );
				builder.Append( "H " );

				length %= 3600;
				under = true;
			}

			if ( under || length >= 60 )
			{
				builder.Append( length / 60 );
				builder.Append( "M " );

				length %= 60;
				under = true;
			}

			builder.Append( length );
			builder.Append( " Seconds (" );
			builder.Append( TicksPerSecond );
			builder.Append( " FPS)" );

			return builder.ToString();
		}

		/// <summary>
		/// 의도적인 타이밍 중지 후 프레임 시간 경과값을 재설정합니다.
		/// </summary>
		public void ResetElapsedTime()
		{
			lasttime = StandardPerformanceCounter;
			framesPerSecond = 0;
			framesThisSecond = 0;
			secondCounter = 0;
		}

		/// <summary>
		/// 타이머 기준 포인트를 설정하고 타이머를 갱신합니다.
		/// </summary>
		/// <param name="updateCallback"> 프레임 호출 갱신 함수를 제공합니다. </param>
		public void Tick( StepTimerCallbackDelegate updateCallback = null )
		{
			var currentTime = StandardPerformanceCounter;
			var timeDelta = currentTime - lasttime;

			lasttime = currentTime;
			secondCounter += timeDelta;

			if ( maxDelta != 0 && timeDelta > maxDelta )
			{
				timeDelta = maxDelta;
			}

			uint lastFrameCount = frameCount;

			if ( isFixedTimeStep )
			{
				if ( Math.Abs( ( long )( timeDelta - targetElapsedTicks ) ) < ( long )TicksPerSecond / 4000 )
				{
					timeDelta = targetElapsedTicks;
				}

				leftOverTicks += timeDelta;

				if ( leftOverTicks >= targetElapsedTicks )
				{
					elapsedTicks = targetElapsedTicks;
					totalTicks += targetElapsedTicks;
					leftOverTicks -= targetElapsedTicks;
					frameCount += 1;

					updateCallback?.Invoke();
				}
			}
			else
			{
				elapsedTicks = timeDelta;
				totalTicks += timeDelta;
				leftOverTicks = 0;
				frameCount += 1;

				updateCallback?.Invoke();
			}

			if ( frameCount != lastFrameCount )
			{
				framesThisSecond += 1;
			}

			if ( secondCounter >= ( ulong )frequency )
			{
				framesPerSecond = framesThisSecond;
				framesThisSecond = 0;
				secondCounter %= frequency;
			}
		}

		/// <summary>
		/// 이전 Tick 함수 호출 이후 경과한 시간을 가져옵니다.
		/// </summary>
		public ulong ElapsedTicks
		{
			get
			{
				return elapsedTicks;
			}
		}

		/// <summary>
		/// 이전 Tick 함수 호출 이후 경과한 시간을 가져옵니다.
		/// </summary>
		public double ElapsedSeconds
		{
			get
			{
				return TicksToSeconds( elapsedTicks );
			}
		}

		/// <summary>
		/// 타이머가 시작된 이후의 총 시간을 가져옵니다.
		/// </summary>
		public ulong TotalTicks
		{
			get
			{
				return totalTicks;
			}
		}

		/// <summary>
		/// 타이머가 시작된 이후의 총 시간을 가져옵니다.
		/// </summary>
		public double TotalSeconds
		{
			get
			{
				return TicksToSeconds( totalTicks );
			}
		}

		/// <summary>
		/// 타이머가 시작된 이후 Tick 함수의 호출 횟수를 가져옵니다.
		/// </summary>
		public ulong TickCount
		{
			get
			{
				return frameCount;
			}
		}

		/// <summary>
		/// 현재 초당 Tick 함수의 호출 횟수를 가져옵니다.
		/// </summary>
		public int TicksPerSecond
		{
			get
			{
				return ( int )framesPerSecond;
			}
		}

		/// <summary>
		/// 타이머가 고정된 시간 비율을 사용하는지 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		public bool IsFixedTimeStep
		{
			get
			{
				return isFixedTimeStep;
			}
			set
			{
				isFixedTimeStep = value;
			}
		}

		/// <summary>
		/// 타이머가 고정된 시간 비율을 사용할 때 호출 빈도를 설정하거나 가져옵니다.
		/// </summary>
		public ulong TargetElapsedTicks
		{
			get
			{
				return targetElapsedTicks;
			}
			set
			{
				targetElapsedTicks = value;
			}
		}

		/// <summary> 
		/// 타이머가 고정된 시간 비율을 사용할 때 호출 빈도를 설정하거나 가져옵니다.
		/// </summary>
		public double TargetElapsedSeconds
		{
			get
			{
				return TicksToSeconds( targetElapsedTicks );
			}
			set
			{
				targetElapsedTicks = SecondsToTicks( value );
			}
		}

		/// <summary>
		/// 타이머가 고정된 시간 비율을 사용할 때 호출 빈도를 설정하거나 가져옵니다.
		/// </summary>
		public int TargetElapsedTicksPerSecond
		{
			get
			{
				return ( int )( 1.0 / TargetElapsedSeconds );
			}
			set
			{
				TargetElapsedSeconds = 1.0 / ( double )value;
			}
		}

		/// <summary>
		/// 프레임 이동 시간 상한을 설정하거나 가져옵니다.
		/// </summary>
		public ulong MaxDeltaTicks
		{
			get
			{
				return maxDelta;
			}
			set
			{
				maxDelta = value;
			}
		}

		/// <summary>
		/// 프레임 이동 시간 상한을 설정하거나 가져옵니다.
		/// </summary>
		public double MaxDeltaSeconds
		{
			get
			{
				return TicksToSeconds( maxDelta );
			}
			set
			{
				maxDelta = SecondsToTicks( value );
			}
		}

		ulong StandardPerformanceCounter
		{
			get
			{
				// 기준 시간으로 경과한 시간을 측정합니다.
				return QueryPerformanceCounter() - standard;
			}
		}

		/// <summary>
		/// 정수 형식 시간 값이 초당 나타내는 값을 가져옵니다.
		/// </summary>
		public static ulong TicksFrequency
		{
			get
			{
				return frequency;
			}
		}

		static ulong SecondsToTicks( double seconds )
		{
			return ( ulong )( seconds * ( double )frequency );
		}

		static double TicksToSeconds( ulong ticks )
		{
			return ( double )ticks / ( double )frequency;
		}

		static StepTimer()
		{
			// Windows의 PerformanceTimer를 사용하여 해상도를 측정합니다.
			frequency = QueryPerformanceFrequency();
		}

		static ulong QueryPerformanceFrequency()
		{
			long value = 0;
			QueryPerformanceFrequency( out value );
			return ( ulong )value;
		}

		static ulong QueryPerformanceCounter()
		{
			long value = 0;
			QueryPerformanceCounter( out value );
			return ( ulong )value;
		}

		[DllImport( "Kernel32.dll" )]
		static extern bool QueryPerformanceCounter( out long lpPerformanceCount );

		[DllImport( "Kernel32.dll" )]
		static extern bool QueryPerformanceFrequency( out long lpFrequency );
	}
}
