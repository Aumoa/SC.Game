namespace SC.Drawing
{
	/// <summary>
	/// Easing 함수를 계산해 애니메이션 키프레임을 업데이트합니다.
	/// </summary>
	public abstract class EaseFunction
	{
		/// <summary>
		/// 함수의 재생 시간을 초단위로 가져옵니다.
		/// </summary>
		readonly double DurationInSeconds;

		readonly string mFunctionName;
		double mTimeSeek = 0;

		/// <summary>
		/// 함수를 시간값에 기초해 계산합니다.
		/// </summary>
		/// <param name="t"> 시간값을 전달받습니다. </param>
		/// <returns> 결과값을 반환합니다. </returns>
		protected abstract double Compute( double t );

		/// <summary>
		/// <see cref="EaseFunction"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="functionName"> 함수의 이름을 전달합니다. </param>
		/// <param name="duration"> 함수의 재생 시간을 전달합니다. </param>
		protected EaseFunction( string functionName, double duration )
		{
			DurationInSeconds = duration;

			mFunctionName = functionName;
		}

		/// <summary>
		/// (<see cref="object"/> 클래스에서 상속 됨.) 현재 개체의 텍스트 표현을 생성하여 반환합니다.
		/// </summary>
		public override string ToString()
		{
			return string.Format( "{0} function.", mFunctionName );
		}

		/// <summary>
		/// 지정된 Easing 함수를 이용해 현재 변환 상태를 갱신합니다.
		/// </summary>
		/// <param name="deltaTime"> 시간 이동값을 전달합니다. </param>
		public void Update( double deltaTime )
		{
			if ( IsStart )
			{
				mTimeSeek += deltaTime;

				if ( mTimeSeek >= DurationInSeconds )
				{
					mTimeSeek = DurationInSeconds;
					IsStart = false;
				}

				double t = mTimeSeek / DurationInSeconds;
				var v = Compute( t );
				if ( IsInvert ) CurrentValue = 1.0 - v;
				else CurrentValue = v;
			}
		}

		/// <summary>
		/// 지정된 Easing 함수를 이용해 현재 변환 상태를 갱신합니다. 고정 시간 탐색 위치를 사용합니다.
		/// </summary>
		/// <param name="timeSeek"> 고정 시간 위치를 전달합니다. </param>
		public void FixedUpdate( double timeSeek )
		{
			if ( IsStart )
			{
				if ( timeSeek >= DurationInSeconds )
				{
					timeSeek = DurationInSeconds;
					IsStart = false;
				}

				double t = timeSeek / DurationInSeconds;
				var v = Compute( t );
				if ( IsInvert ) CurrentValue = 1.0 - v;
				else CurrentValue = v;
			}
		}

		/// <summary>
		/// Easing 함수의 보간을 시작합니다. 시간 위치를 시작으로 설정합니다.
		/// </summary>
		public void Start()
		{
			if ( IsStart == false )
			{
				IsStart = true;
			}

			mTimeSeek = 0;
			var v = Compute( 0 );
			if ( IsInvert ) CurrentValue = 1.0 - v;
			else CurrentValue = v;
		}

		/// <summary>
		/// Easing 함수의 보간을 종료합니다. 시간 위치를 마지막으로 설정합니다.
		/// </summary>
		public void Stop()
		{
			if ( IsStart )
			{
				IsStart = false;
			}

			mTimeSeek = DurationInSeconds;
			var v = Compute( 1 );
			if ( IsInvert ) CurrentValue = 1.0 - v;
			else CurrentValue = v;
		}

		/// <summary>
		/// 함수의 보간이 시작되었는지 검사합니다.
		/// </summary>
		public bool IsStart { get; private set; } = false;

		/// <summary>
		/// 함수의 값을 반전해서 가져옵니다.
		/// </summary>
		public bool IsInvert { get; set; } = false;

		/// <summary>
		/// 함수의 보간 위치를 가져옵니다. 0에서 1사이의 값을 가집니다.
		/// </summary>
		public double CurrentT { get; } = 0;

		/// <summary>
		/// 함수의 Easing 보간 값을 가져옵니다.
		/// </summary>
		public double CurrentValue { get; private set; } = 0;
	}
}