#pragma once

namespace SC::Game
{
	/// <summary>
	/// �̵�, Ȯ�� ��� �� ȸ�� Ű�������� ��� ���Ե� ���� ��ü�� ǥ���մϴ�.
	/// </summary>
	public value struct KeyframePair
	{
		Keyframe Translation;
		Keyframe Scaling;
		KeyframeQ Rotation;

		/// <summary>
		/// <see cref="KeyframePair"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="translation"> �̵� ��ȯ ���� �����մϴ�. </param>
		/// <param name="scale"> ��� ��ȯ ���� �����մϴ�. </param>
		/// <param name="rotation"> ȸ�� ��ȯ ���� �����մϴ�. </param>
		KeyframePair( Keyframe translation, Keyframe scale, KeyframeQ rotation )
		{
			this->Translation = translation;
			this->Scaling = scale;
			this->Rotation = rotation;
		}

		/// <summary>
		/// ��� Ű�����Ӱ� ������ �����մϴ�.
		/// </summary>
		/// <param name="right"> ��� Ű�������� �����մϴ�. </param>
		/// <param name="t"> ���� ��� ���� �����մϴ�. </param>
		KeyframePair Interpolate( KeyframePair right, float t )
		{
			KeyframePair pair;

			auto invt = 1.0f - t;

			pair.Translation.TimePos = Translation.TimePos * invt + right.Translation.TimePos * t;
			pair.Translation.Value = System::Numerics::Vector3::Lerp( Translation.Value, right.Translation.Value, t );

			pair.Scaling.TimePos = Scaling.TimePos * invt + right.Scaling.TimePos * t;
			pair.Scaling.Value = System::Numerics::Vector3::Lerp( Scaling.Value, right.Scaling.Value, t );

			pair.Rotation.TimePos = Rotation.TimePos * invt + right.Rotation.TimePos * t;
			pair.Rotation.Value = System::Numerics::Quaternion::Slerp( Rotation.Value, right.Rotation.Value, t );

			return pair;
		}
	};
}