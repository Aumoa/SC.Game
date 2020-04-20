using namespace SC;
using namespace SC::Game;

using namespace System;

AnimationState::AnimationState( String^ xName ) : Asset( xName )
{

}

AnimationClip^ AnimationState::Clip::get()
{
	return mClip;
}

void AnimationState::Clip::set( AnimationClip^ value )
{
	mClip = value;
}