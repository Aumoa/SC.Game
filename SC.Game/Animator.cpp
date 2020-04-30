using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;
using namespace System::Collections::Generic;
using namespace System::Linq;

using namespace std;

void Animator::SetInput( CDeviceContext& deviceContext )
{
	Start();

	if ( mBoneTransform && mBoneTransform->size() )
	{
		deviceContext.SetComputeRootShaderResourceView( Slot_Skinning_BoneTransform, mFinalTransformBuffer->GetGPUVirtualAddress() );
	}
}

void Animator::Start()
{
	if ( mRefreshed )
	{
		return;
	}

	int numBones = Object->GetComponentsInChildren<Bone^>()->Count;

	if ( !mBoneTransform )
	{
		mBoneTransform = new std::vector<tag_Bone>();
		mFinalTransform = new std::vector<tag_BoneTransform>();
	}
	mBoneTransform->resize( numBones );
	mFinalTransform->resize( numBones );

	if ( numBones )
	{
		mFinalTransformBuffer = new LargeHeap( D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, sizeof( tag_BoneTransform ) * numBones );
		InitializeOffset( Object, -1 );
	}
	else
	{
		mFinalTransformBuffer = nullptr;
	}

	mRefreshed = true;
}

void Animator::FixedUpdate()
{
	Start();

	if ( mController && mBoneTransform )
	{
		Transistor();

		if ( !mKeyframeUpdated )
		{
			mCurrentState.Interpolate( Time::FixedDeltaTime );
			mPrevState.Interpolate( Time::FixedDeltaTime );
			UpdateBlend( Time::FixedDeltaTime );

			UpdateToRoot( Object, -1 );
			ReplaceToRoot();

			if ( mCurrentState.Clip->mIsEmpty )
			{
				mKeyframeUpdated = true;
			}

			if ( mFinalTransformBuffer )
			{
				auto block = ( tag_BoneTransform* )mFinalTransformBuffer->Map();
				memcpy( block, mFinalTransform->data(), sizeof( tag_BoneTransform ) * mFinalTransform->size() );
				mFinalTransformBuffer->Unmap();
			}
		}
	}
}

Animator::Animator()
{

}

Animator::~Animator()
{
	this->!Animator();
}

Animator::!Animator()
{
	ComPtr<IUnknown> pUnknown;
	pUnknown.Attach( mFinalTransformBuffer );
	App::GCAdd( move( pUnknown ) );

	if ( mBoneTransform )
	{
		delete mBoneTransform;
		mBoneTransform = nullptr;
	}

	if ( mFinalTransform )
	{
		delete mFinalTransform;
		mFinalTransform = nullptr;
	}
}

Object^ Animator::Clone()
{
	auto clone = gcnew Animator();

	clone->mController = mController;
	clone->mAnimVars = gcnew Dictionary<String^, System::Object^>( mAnimVars );

	clone->mCurrentState = mCurrentState;
	clone->mPrevState = mPrevState;
	clone->mBlendTime = mBlendTime;

	return clone;
}

Object^ Animator::GetVar( String^ vName )
{
	if ( mAnimVars->ContainsKey( vName ) )
	{
		return mAnimVars[vName];
	}
	else
	{
		auto params = mController->mParameters;

		if ( params->ContainsKey( vName ) )
		{
			auto value = params[vName];
			mAnimVars->Add( vName, value );
			return value;
		}
		else
		{
			return nullptr;
		}
	}
}

void Animator::SetVar( String^ vName, System::Object^ value )
{
	if ( mAnimVars->ContainsKey( vName ) )
	{
		mAnimVars[vName] = value;
	}
	else
	{
		mAnimVars->Add( vName, value );
	}
}

AnimatorController^ Animator::Controller::get()
{
	return mController;
}

void Animator::Controller::set( AnimatorController^ value )
{
	mController = value;
	mAnimVars = value->MakeParameters();
	mCurrentState = MakeStateMachine( value->DefaultState );
	mPrevState = { };
}

void Animator::InitializeOffset( GameObject^ gameObject, int parent )
{
	auto bone = gameObject->GetComponent<Bone^>();

	if ( bone )
	{
		auto idx = bone->Index;
		auto trp = gameObject->Transform;
		auto pos = trp->LocalPosition;
		auto scale = trp->LocalScale;
		auto quat = trp->LocalRotation;

		auto offset =
			Matrix4x4::CreateScale( scale ) *
			Matrix4x4::CreateFromQuaternion( quat ) *
			Matrix4x4::CreateTranslation( pos );

		Assign( mBoneTransform->at( idx ).Offset, offset );
		Assign( mBoneTransform->at( idx ).ToRoot, Matrix4x4::Identity );
		Assign( mFinalTransform->at( idx ).World, Matrix4x4::Identity );

		parent = idx;
	}

	for ( int i = 0; i < gameObject->NumChilds; ++i )
	{
		InitializeOffset( gameObject->GetChild( i ), parent );
	}
}

void Animator::UpdateToRoot( GameObject^ gameObject, int parent )
{
	auto bone = gameObject->GetComponent<Bone^>();

	if ( bone )
	{
		auto idx = bone->Index;
		auto name = bone->Name;

		auto transform = Matrix4x4::Identity;

		if ( mCurrentState.Keyframes->ContainsKey( name ) )
		{
			auto key = mCurrentState.Keyframes[name];

			transform =
				Matrix4x4::CreateScale( key.Scaling.Value ) *
				Matrix4x4::CreateFromQuaternion( key.Rotation.Value ) *
				Matrix4x4::CreateTranslation( key.Translation.Value );
		}

		Matrix4x4 parentTransform = Matrix4x4::Identity;

		if ( parent != -1 )
		{
			Assign( parentTransform, mBoneTransform->at( parent ).ToRoot );
		}

		Assign( mBoneTransform->at( idx ).ToRoot, transform * parentTransform );
		parent = idx;
	}

	for ( int i = 0; i < gameObject->NumChilds; ++i )
	{
		UpdateToRoot( gameObject->GetChild( i ), parent );
	}
}

void Animator::ReplaceToRoot()
{
	for ( int i = 0, count = ( int )mBoneTransform->size(); i < count; ++i )
	{
		auto& bt = mBoneTransform->at( i );

		Matrix4x4 offset;
		Assign( offset, bt.Offset );
		Matrix4x4 toRoot;
		Assign( toRoot, bt.ToRoot );

		Matrix4x4 final = offset * toRoot;

		Assign( mFinalTransform->at( i ).World, final );
	}
}

void Animator::Transistor()
{
	auto conds = mController->GetTransition( mCurrentState.Name );

	if ( conds )
	{
		for each ( auto i in conds )
		{
			bool change = false;
			bool checkIf = true;

			if ( i.HasExitTime )
			{
				if ( mCurrentState.TimePos < ( mCurrentState.Duration - i.BlendTime ) )
				{
					checkIf = false;
				}
			}

			if ( checkIf )
			{

				if ( String::IsNullOrEmpty( i.VarName ) )
				{
					change = true;
				}
				else
				{
					auto var = GetVar( i.VarName );
					auto type = var->GetType();
					if ( type == Trigger::typeid )
					{
						SetVar( i.VarName, Trigger( false ) );
						change = true;
					}
					else if ( i.Condition( var ) )
					{
						change = true;
					}
				}
			}

			if ( change )
			{
				if ( i.BlendTime != 0 )
				{
					mPrevState = mCurrentState;
					mBlendTime = i.BlendTime;
				}

				mCurrentState = MakeStateMachine( i.To );
				mKeyframeUpdated = false;
				break;
			}
		}
	}
}

void Animator::UpdateBlend( float timeDelta )
{
	if ( mPrevState.Clip )
	{
		if ( mCurrentState.TimePos > mBlendTime )
		{
			mPrevState = StateMachine();
		}
		else
		{
			float t = mCurrentState.TimePos / mBlendTime;

			List<String^>^ keyList = Enumerable::ToList<String^>( mCurrentState.Keyframes->Keys );
			List<KeyframePair>^ valueList = Enumerable::ToList<KeyframePair>( mCurrentState.Keyframes->Values );

			for ( int i = 0; i < keyList->Count; ++i )
			{
				auto key = keyList[i];

				if ( mPrevState.Keyframes->ContainsKey( key ) )
				{
					auto key1 = mPrevState.Keyframes[key];
					auto key2 = valueList[i];

					mCurrentState.Keyframes[key] = key1.Interpolate( key2, t );
				}
			}
		}
	}
}

StateMachine Animator::MakeStateMachine( String^ name )
{
	StateMachine machine;

	machine.State = mController->GetState( name );
	if ( machine.State )
	{
		machine.Name = name;
		machine.Clip = machine.State->Clip;
		machine.Duration = machine.Clip->Duration;
		machine.Keyframes = machine.Clip->MakeInterpolateMap();
		machine.TimePos = 0;
	}
	else
	{
		return mCurrentState;
	}

	return machine;
}