#pragma once

namespace SC::Game
{
	/// <summary>
	/// �ϼ��� Ű������ ����� ǥ���մϴ�.
	/// </summary>
	public value struct Keyframes
	{
		/// <summary>
		/// �̵� �ִϸ��̼� Ű������ ����� �����մϴ�.
		/// </summary>
		System::Collections::Generic::IList<Keyframe>^ Translation;

		/// <summary>
		/// ��� �ִϸ��̼� Ű������ ����� �����մϴ�.
		/// </summary>
		System::Collections::Generic::IList<Keyframe>^ Scaling;

		/// <summary>
		/// ȸ�� �ִϸ��̼� Ű������ ����� �����մϴ�.
		/// </summary>
		System::Collections::Generic::IList<KeyframeQ>^ Rotation;

		/// <summary>
		/// ���� Ű������ ��Ͽ��� �ش� �ð��� ��ġ�ϴ� ������ Ű�������� �����ɴϴ�.
		/// </summary>
		/// <param name="timePos"> �ð� ���� �����մϴ�. </param>
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
		/// �ִϸ��̼��� ������ Ű������ �ð� ��ġ�� �����ɴϴ�.
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