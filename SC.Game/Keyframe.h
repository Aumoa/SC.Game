#pragma once

namespace SC::Game
{
	/// <summary>
	/// 3���� �����е� �Ǽ� ���� ����ϴ� �ִϸ��̼� ���� Ű�������� ǥ���մϴ�.
	/// </summary>
	public value struct Keyframe : public System::IEquatable<Keyframe>
	{
		/// <summary>
		/// Ű�������� �ð� ���� �� ������ �����մϴ�.
		/// </summary>
		float TimePos;

		/// <summary>
		/// Ű�������� ���� ���� �����մϴ�.
		/// </summary>
		System::Numerics::Vector3 Value;

		/// <summary>
		/// <see cref="Keyframe"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="timePos"> Ű�������� �ð� ���� �����մϴ�. </param>
		/// <param name="value"> Ű�������� ���� �����մϴ�. </param>
		Keyframe( float timePos, System::Numerics::Vector3 value )
		{
			this->TimePos = timePos;
			this->Value = value;
		}

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) ���� Ű�����ӿ� ���� �ؽ�Ʈ ������ �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override
		{
			return System::String::Format( "Keyframe: {0:F2}, {1:F4}", TimePos, Value );
		}

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) �� ��ü�� ���� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ���� ��� ��ü�� �����մϴ�. </param>
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
		/// (<see cref="System::IEquatable"/> �������̽����� ���� ��.) �� ��ü�� ���� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ���� ��� ��ü�� �����մϴ�. </param>
		virtual bool Equals( Keyframe right )
		{
			return TimePos == right.TimePos && Value == right.Value;
		}

		/// <summary>
		/// �ð� ������� ���� Ű�����Ӱ� ��� Ű������ ���̿� ��ġ�ϴ��� �˻��մϴ�.
		/// </summary>
		/// <param name="right"> ��� Ű�������� �����մϴ�. </param>
		/// <param name="timePos"> �ð� ������� �����մϴ�. </param>
		bool CheckIf( Keyframe right, float timePos )
		{
			return timePos >= TimePos && timePos < right.TimePos;
		}

		/// <summary>
		/// �ð� ����� ����Ͽ� ��� Ű�����Ӱ� �����մϴ�.
		/// </summary>
		/// <param name="right"> ��� Ű�������� �����մϴ�. </param>
		/// <param name="timePos"> �ð� ������� �����մϴ�. </param>
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