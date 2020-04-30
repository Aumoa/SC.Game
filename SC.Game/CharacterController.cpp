using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace physx;

CharacterController::CharacterController() : Rigidbody()
{

}

Object^ CharacterController::Clone()
{
	auto clone = gcnew CharacterController();
	clone->mRadius = mRadius;
	clone->mHeight = mHeight;
	clone->mSlopeLimit = mSlopeLimit;
	clone->mDensity = mDensity;
	return clone;
}

void CharacterController::MovePosition( Vector3 value )
{
	value = Vector3::Subtract( value, Transform->Position );

	PxVec3 disp;
	Assign( disp, value );
	auto flag = mController->move( disp, 0, Time::FixedDeltaTime, PxControllerFilters() );
}

float CharacterController::Radius::get()
{
	return mRadius;
}

void CharacterController::Radius::set( float value )
{
	mRadius = value;
}

float CharacterController::Height::get()
{
	return mHeight;
}

void CharacterController::Height::set( float value )
{
	mHeight = value;
}

float CharacterController::SlopeLimit::get()
{
	return mSlopeLimit;
}

void CharacterController::SlopeLimit::set( float value )
{
	mSlopeLimit = value;

	if ( mController )
	{
		mController->setSlopeLimit( mSlopeLimit );
	}
}

float CharacterController::Density::get()
{
	return mDensity;
}

void CharacterController::Density::set( float value )
{
	mDensity = value;
}

float CharacterController::StepOffset::get()
{
	return mStepOffset;
}

void CharacterController::StepOffset::set( float value )
{
	mStepOffset = value;

	if ( mController )
	{
		mController->setStepOffset( value );
	}
}