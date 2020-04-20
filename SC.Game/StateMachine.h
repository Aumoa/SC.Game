#pragma once

namespace SC::Game
{
	ref class AnimationState;
	ref class AnimationClip;

	value struct StateMachine
	{
		System::String^ Name;
		AnimationState^ State;
		AnimationClip^ Clip;
		float Duration;
		System::Collections::Generic::IDictionary<System::String^, KeyframePair>^ Keyframes;
		float TimePos;

		void Interpolate( float timeDelta );
	};
}