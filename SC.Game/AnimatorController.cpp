using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;

IDictionary<String^, Object^>^ AnimatorController::MakeParameters()
{
	return gcnew Dictionary<String^, Object^>( mParameters );
}

AnimatorController::AnimatorController( String^ xName ) : Asset( xName )
{
	mStates = gcnew Dictionary<String^, AnimationState^>();
	mParameters = gcnew Dictionary<String^, Object^>();
	mTransitionCondition = gcnew Dictionary<String^, IList<AnimationTransitionCondition>^>();
}

void AnimatorController::AddState( AnimationState^ state, bool isDefault )
{
	AddState( state->Name, state, isDefault );
}

void AnimatorController::AddState( String^ stateNameOverride, AnimationState^ state, bool isDefault )
{
	if ( mStates->ContainsKey( stateNameOverride ) )
	{
		mStates[stateNameOverride] = state;
	}
	else
	{
		mStates->Add( stateNameOverride, state );
		if ( isDefault ) mDefaultState = stateNameOverride;
		else if ( mDefaultState == nullptr ) mDefaultState = stateNameOverride;
	}
}

void AnimatorController::RemoveState( String^ stateName )
{
	mStates->Remove( stateName );
}

AnimationState^ AnimatorController::GetState( String^ stateName )
{
	if ( mStates->ContainsKey( stateName ) )
	{
		return mStates[stateName];
	}
	else
	{
		return nullptr;
	}
}

void AnimatorController::AddVar( String^ stateName, Object^ value )
{
	if ( mParameters->ContainsKey( stateName ) )
	{
		mParameters[stateName] = value;
	}
	else
	{
		mParameters->Add( stateName, value );
	}
}

void AnimatorController::RemoveVar( String^ stateName )
{
	mParameters->Remove( stateName );
}

Object^ AnimatorController::GetVar( String^ varName )
{
	if ( mParameters->ContainsKey( varName ) )
	{
		return mParameters[varName];
	}
	else
	{
		return nullptr;
	}
}

void AnimatorController::AddTransition( String^ from, AnimationTransitionCondition value )
{
	if ( mTransitionCondition->ContainsKey( from ) )
	{
		mTransitionCondition[from]->Add( value );
	}
	else
	{
		auto list = gcnew List<AnimationTransitionCondition>();
		list->Add( value );
		mTransitionCondition->Add( from, list );
	}
}

void AnimatorController::RemoveTransition( String^ from, AnimationTransitionCondition value )
{
	if ( mTransitionCondition->ContainsKey( from ) )
	{
		auto list = mTransitionCondition[from];

		for each ( auto v in list )
		{
			bool check = true;

			if ( value.To != nullptr )
			{
				if ( v.To == value.To )
				{
					check = check && true;
				}
				else
				{
					check = false;
				}
			}

			if ( value.VarName != nullptr )
			{
				if ( v.VarName == value.VarName )
				{
					check = check && true;
				}
				else
				{
					check = false;
				}
			}

			list->Remove( v );
			break;
		}
	}
}

IList<AnimationTransitionCondition>^ AnimatorController::GetTransition( String^ from )
{
	if ( mTransitionCondition->ContainsKey( from ) )
	{
		return mTransitionCondition[from];
	}
	else
	{
		return nullptr;
	}
}

String^ AnimatorController::DefaultState::get()
{
	return mDefaultState;
}