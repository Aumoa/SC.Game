#pragma once

namespace SC::Game
{
	/// <summary>
	/// 완성된 키프레임 목록을 표현합니다.
	/// </summary>
	public value struct Keyframes
	{
		/// <summary>
		/// 이동 애니메이션 키프레임 목록을 설정합니다.
		/// </summary>
		System::Collections::Generic::IList<Keyframe>^ Translation;

		/// <summary>
		/// 비례 애니메이션 키프레임 목록을 설정합니다.
		/// </summary>
		System::Collections::Generic::IList<Keyframe>^ Scaling;

		/// <summary>
		/// 회전 애니메이션 키프레임 목록을 설정합니다.
		/// </summary>
		System::Collections::Generic::IList<KeyframeQ>^ Rotation;

		/// <summary>
		/// 변형 키프레임 목록에서 해당 시간과 일치하는 보간된 키프레임을 가져옵니다.
		/// </summary>
		/// <param name="timePos"> 시간 값을 전달합니다. </param>
		KeyframePair Interpolate( float timePos )
		{
			using namespace std;

			Keyframe trans;
			Keyframe scale;
			KeyframeQ quat;

			if ( Translation->Count == 0 )
			{
				trans.TimePos = timePos;
				trans.Value = System::Numerics::Vector3::Zero;
			}
			else
			{
				trans = InterpolateHelper( timePos, Translation );
			}

			if ( Scaling->Count == 0 )
			{
				scale.TimePos = timePos;
				scale.Value = System::Numerics::Vector3::One;
			}
			else
			{
				scale = InterpolateHelper( timePos, Scaling );
			}

			if ( Rotation->Count == 0 )
			{
				quat.TimePos = timePos;
				quat.Value = System::Numerics::Quaternion::Identity;
			}
			else
			{
				quat = InterpolateHelper( timePos, Rotation );
			}

			return KeyframePair( trans, scale, quat );
		}

		/// <summary>
		/// 애니메이션의 마지막 키프레임 시간 위치를 가져옵니다.
		/// </summary>
		property float Duration
		{
			float get()
			{
				float dur = 0;

				for ( int i = 0, count = Translation->Count; i < count; ++i )
				{
					auto key = Translation[i].TimePos;
					dur = std::max( dur, key );
				}

				for ( int i = 0, count = ( int )Scaling->Count; i < count; ++i )
				{
					auto key = Scaling[i].TimePos;
					dur = std::max( dur, key );
				}

				for ( int i = 0, count = ( int )Rotation->Count; i < count; ++i )
				{
					auto key = Rotation[i].TimePos;
					dur = std::max( dur, key );
				}

				return dur;
			}
		}

	private:
		Keyframe InterpolateHelper( float timePos, System::Collections::Generic::IList<Keyframe>^ collection )
		{
			int indexOf = -1;

			for each ( auto lower in collection )
			{
				if ( lower.TimePos < timePos )
				{
					++indexOf;
				}
				else
				{
					break;
				}
			}

			if ( indexOf == -1 )
			{
				return collection[0];
			}

			else if ( indexOf >= collection->Count - 1 )
			{
				return collection[collection->Count - 1];
			}

			else
			{
				auto left = collection[indexOf];
				auto right = collection[indexOf + 1];

				return left.Interpolate( right, timePos );
			}
		}

		KeyframeQ InterpolateHelper( float timePos, System::Collections::Generic::IList<KeyframeQ>^ collection )
		{
			int indexOf = -1;

			for each ( auto lower in collection )
			{
				if ( lower.TimePos < timePos )
				{
					++indexOf;
				}
				else
				{
					break;
				}
			}

			if ( indexOf == -1 )
			{
				return collection[0];
			}

			else if ( indexOf >= collection->Count - 1 )
			{
				return collection[collection->Count - 1];
			}

			else
			{
				auto left = collection[indexOf];
				auto right = collection[indexOf + 1];

				return left.Interpolate( right, timePos );
			}
		}
	};
}