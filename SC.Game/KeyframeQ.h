#pragma once

namespace SC::Game
{
	/// <summary>
	/// 4���� �����е� �Ǽ� ���� ����ϴ� �ִϸ��̼� ���� Ű�������� ǥ���մϴ�.
	/// </summary>
	public value struct KeyframeQ : public System::IEquatable<KeyframeQ>
	{
		/// <summary>
		/// Ű�������� �ð� ���� �� ������ �����մϴ�.
		/// </summary>
		float TimePos;

		/// <summary>
		/// Ű�������� ���� ���� �����մϴ�.
		/// </summary>
		System::Numerics::Quaternion Value;

		/// <summary>
		/// <see cref="Keyframe"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="timePos"> Ű�������� �ð� ���� �����մϴ�. </param>
		/// <param name="value"> Ű�������� ���� �����մϴ�. </param>
		KeyframeQ( float timePos, System::Numerics::Quaternion value )
		{
			this->TimePos = timePos;
			this->Value = value;
		}

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) �� ��ü�� ���� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ��� ��ü�� �����մϴ�. </param>
		bool Equals( System::Object^ right ) override
		{
			if ( right->GetType() == KeyframeQ::typeid )
			{
				return Equals( ( KeyframeQ )right );
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// (<see cref="System::IEquatable"/> �������̽����� ���� ��.) �� ��ü�� ���� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ��� ��ü�� �����մϴ�. </param>
		virtual bool Equals( KeyframeQ right )
		{
			return TimePos == right.TimePos && Value == right.Value;
		}

		/// <summary>
		/// �ð� ������� ���� Ű�����Ӱ� ��� Ű������ ���̿� ��ġ�ϴ��� �˻��մϴ�.
		/// </summary>
		/// <param name="right"> ��� Ű�������� �����մϴ�. </param>
		/// <param name="timePos"> �ð� ������� �����մϴ�. </param>
		bool CheckIf( KeyframeQ right, float timePos )
		{
			return timePos >= TimePos && timePos < right.TimePos;
		}

		/// <summary>
		/// �ð� ����� ����Ͽ� ��� Ű�����Ӱ� �����մϴ�.
		/// </summary>
		/// <param name="right"> ��� Ű�������� �����մϴ�. </param>
		/// <param name="timePos"> �ð� ������� �����մϴ�. </param>
		KeyframeQ Interpolate( KeyframeQ right, float timePos )
		{
			auto deltaT = right.TimePos - TimePos;
			auto deltaV = System::Numerics::Quaternion::Subtract( right.Value, Value );

			auto t = ( timePos - TimePos ) / deltaT;

			KeyframeQ k;
			k.TimePos = timePos;
			k.Value = System::Numerics::Quaternion::Slerp( Value, right.Value, t );

			return k;
		}
	};
}