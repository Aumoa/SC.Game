#pragma once

namespace SC::Game
{
	/// <summary>
	/// 이동, 확대 축소 및 회전 키프레임이 모두 포함된 단일 개체를 표현합니다.
	/// </summary>
	public value struct KeyframePair
	{
		Keyframe Translation;
		Keyframe Scaling;
		KeyframeQ Rotation;

		/// <summary>
		/// <see cref="KeyframePair"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="translation"> 이동 변환 값을 전달합니다. </param>
		/// <param name="scale"> 비례 변환 값을 전달합니다. </param>
		/// <param name="rotation"> 회전 변환 값을 전달합니다. </param>
		KeyframePair( Keyframe translation, Keyframe scale, KeyframeQ rotation )
		{
			this->Translation = translation;
			this->Scaling = scale;
			this->Rotation = rotation;
		}

		/// <summary>
		/// 대상 키프레임과 보간을 수행합니다.
		/// </summary>
		/// <param name="right"> 대상 키프레임을 전달합니다. </param>
		/// <param name="t"> 보간 계수 값을 전달합니다. </param>
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