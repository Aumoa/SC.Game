using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Numerics;

using namespace std;

void AnimationClip::ComputeDur()
{
	mDuration = 0.0f;

	for each ( auto i in mKeyframes )
	{
		mDuration = mDuration < i.Value.Duration ? i.Value.Duration : mDuration;
	}
}

IDictionary<String^, KeyframePair>^ AnimationClip::MakeInterpolateMap()
{
	auto map = gcnew Dictionary<String^, KeyframePair>();

	for each ( auto i in mKeyframes )
	{
		map->Add( i.Key, KeyframePair() );
	}

	return map;
}

void AnimationClip::Interpolate( float timePos, IDictionary<String^, KeyframePair>^ interpolated )
{
	if ( mIsLoop )
	{
		timePos = fmod( timePos, mDuration );
	}

	for each ( auto i in mKeyframes )
	{
		interpolated[i.Key] = i.Value.Interpolate( timePos );
	}
}

AnimationClip::AnimationClip( String^ xName ) : Asset( xName )
{
	mKeyframes = gcnew Dictionary<String^, Keyframes>();
}

void AnimationClip::RemoveKeyframes( String^ boneName )
{
	if ( mKeyframes->ContainsKey( boneName ) )
	{
		mKeyframes->Remove( boneName );
	}

	ComputeDur();
	if ( !mIsEmpty )
	{
		mIsEmpty = !mKeyframes->Count;
	}
}

void AnimationClip::AddKeyframes( String^ boneName, Keyframes keyframes )
{
	if ( mKeyframes->ContainsKey( boneName ) )
	{
		mKeyframes[boneName] = keyframes;
	}
	else
	{
		mKeyframes->Add( boneName, keyframes );
	}

	ComputeDur();

	// 애니메이션 장면 내 애니메이션 모양이 변경되지 않을 경우를 검사합니다.
	if ( keyframes.Translation->Count < 2 && keyframes.Scaling->Count < 2 && keyframes.Rotation->Count < 2 )
	{
		mIsEmpty = mIsEmpty && true;
	}
	else
	{
		mIsEmpty = false;
	}
}

void AnimationClip::RenameKeyframes( String^ boneName, String^ rename, float scaleFactor )
{
	if ( mKeyframes->ContainsKey( boneName ) )
	{
		auto keyframes = mKeyframes[boneName];
		mKeyframes->Remove( boneName );
		mKeyframes[rename] = keyframes;

		if ( scaleFactor < 0.99f || scaleFactor > 1.01f )
		{
			for ( int i = 0; i < keyframes.Translation->Count; ++i )
			{
				auto keyframe = keyframes.Translation[i];
				keyframe.Value *= scaleFactor;
				keyframes.Translation[i] = keyframe;
			}
		}
	}
}

Keyframes AnimationClip::GetKeyframes( String^ boneName )
{
	if ( mKeyframes->ContainsKey( boneName ) )
	{
		return mKeyframes[boneName];
	}
	else
	{
		return Keyframes();
	}
}

bool AnimationClip::HasKeyframes( String^ boneName )
{
	return mKeyframes->ContainsKey( boneName );
}

float AnimationClip::Duration::get()
{
	return mDuration;
}

bool AnimationClip::IsLoop::get()
{
	return mIsLoop;
}

void AnimationClip::IsLoop::set( bool value )
{
	mIsLoop = value;
}