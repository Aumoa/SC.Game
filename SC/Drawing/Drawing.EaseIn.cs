﻿namespace SC.Drawing
{
	/// <summary>
	/// 진입 함수를 사용하는 Easing 함수를 계산합니다.
	/// </summary>
	public class EaseIn : EaseFunction
	{
		/// <summary>
		/// (<see cref="EaseFunction"/> 클래스에서 상속 됨.) 진입 함수를 사용하여 함수를 계산합니다.
		/// </summary>
		/// <param name="t"> 시간값을 전달받습니다. </param>
		/// <returns> 결과값을 반환합니다. </returns>
		protected override double Compute( double t )
		{
			return t * t;
		}

		/// <summary>
		/// <see cref="EaseIn"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="duration"> 함수의 재생 시간을 전달합니다. </param>
		public EaseIn( double duration ) : base( "EaseIn", duration )
		{

		}
	}
}