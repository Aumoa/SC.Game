using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace physx;

void CapsuleCollider::Update()
{
	if ( mHasUpdate )
	{
		auto geo = static_cast< PxCapsuleGeometry* >( mGeometry );
		geo->radius = ( PxReal )( mRadius );
		geo->halfHeight = ( PxReal )( mHalfHeight );
	}

	Collider::Update();
}

CapsuleCollider::CapsuleCollider() : Collider()
{
	auto capsuleGeo = new PxCapsuleGeometry();
	capsuleGeo->radius = 1.0f;
	capsuleGeo->halfHeight = 1.0f;

	mGeometry = capsuleGeo;
}

Object^ CapsuleCollider::Clone()
{
	auto clone = gcnew CapsuleCollider();
	CloneAs( clone );
	clone->mHalfHeight = mHalfHeight;
	clone->mRadius = mRadius;
	return clone;
}

float CapsuleCollider::Height::get()
{
	return mHalfHeight * 2.0f;
}

void CapsuleCollider::Height::set( float value )
{
	mHalfHeight = value * 0.5f;
	mHasUpdate = true;
}

float CapsuleCollider::Radius::get()
{
	return mRadius;
}

void CapsuleCollider::Radius::set( float value )
{
	mRadius = value;
	mHasUpdate = true;
}