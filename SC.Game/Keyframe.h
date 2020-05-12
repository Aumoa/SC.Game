#pragma once

namespace SC::Game
{
	/// <summary>
	/// 3차원 단정밀도 실수 값을 사용하는 애니메이션 단일 키프레임을 표현합니다.
	/// </summary>
	public value struct Keyframe : public System::IEquatable<Keyframe>
	{
		/// <summary>
		/// 키프레임의 시간 값을 초 단위로 설정합니다.
		/// </summary>
		float TimePos;

		/// <summary>
		/// 키프레임의 변형 값을 설정합니다.
		/// </summary>
		System::Numerics::Vector3 Value;

		/// <summary>
		/// <see cref="Keyframe"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="timePos"> 키프레임의 시간 값을 전달합니다. </param>
		/// <param name="value"> 키프레임의 값을 전달합니다. </param>
		Keyframe( float timePos, System::Numerics::Vector3 value )
		{
			this->TimePos = timePos;
			this->Value = value;
		}

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 단일 키프레임에 대한 텍스트 형식을 생성하여 반환합니다.
		/// </summary>
		System::String^ ToString() override
		{
			return System::String::Format( "Keyframe: {0:F2}, {1:F4}", TimePos, Value );
		}

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 두 개체의 값이 같은지 비교합니다.
		/// </summary>
		/// <param name="right"> 비교할 대상 개체를 전달합니다. </param>
		bool Equals( System::Object^ right ) override
		{
			if ( right->GetType() == Keyframe::typeid )
			{
				return Equals( ( Keyframe )right );
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// (<see cref="System::IEquatable"/> 인터페이스에서 구현 됨.) 두 개체의 값이 같은지 비교합니다.
		/// </summary>
		/// <param name="right"> 비교할 대상 개체를 전달합니다. </param>
		virtual bool Equals( Keyframe right )
		{
			return TimePos == right.TimePos && Value == right.Value;
		}

		/// <summary>
		/// 시간 경과값이 현재 키프레임과 대상 키프레임 사이에 위치하는지 검사합니다.
		/// </summary>
		/// <param name="right"> 대상 키프레임을 전달합니다. </param>
		/// <param name="timePos"> 시간 경과값을 전달합니다. </param>
		bool CheckIf( Keyframe right, float timePos )
		{
			return timePos >= TimePos && timePos < right.TimePos;
		}

		/// <summary>
		/// 시간 경과를 사용하여 대상 키프레임과 보간합니다.
		/// </summary>
		/// <param name="right"> 대상 키프레임을 전달합니다. </param>
		/// <param name="timePos"> 시간 경과값을 전달합니다. </param>
		Keyframe Interpolate( Keyframe right, float timePos )
		{
			auto deltaT = right.TimePos - TimePos;
			auto deltaV = System::Numerics::Vector3::Subtract( right.Value, Value );

			auto t = ( timePos - TimePos ) / deltaT;

			Keyframe k;
			k.TimePos = timePos;
			k.Value = System::Numerics::Vector3::Lerp( Value, right.Value, t );

			return k;
		}
	};
}