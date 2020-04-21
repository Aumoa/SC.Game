using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace physx;

void BoxCollider::Update()
{
	if ( mHasUpdate || Transform->IsUpdated )
	{
		auto geo = static_cast< PxBoxGeometry* >( mGeometry );
		Assign( geo->halfExtents, mHalfExtents * Transform->Scale );

		mHasUpdate = true;
	}

	Collider::Update();
}

BoxCollider::BoxCollider() : Collider()
{
	mHalfExtents = Vector3( 1.0f, 1.0f, 1.0f );

	auto geo = new PxBoxGeometry();
	Assign( geo->halfExtents, mHalfExtents );

	mGeometry = geo;
}

Object^ BoxCollider::Clone()
{
	auto clone = gcnew BoxCollider();
	CloneAs( clone );
	clone->mHalfExtents = mHalfExtents;
	return clone;
}

Vector3 BoxCollider::HalfExtents::get()
{
	return mHalfExtents;
}

void BoxCollider::HalfExtents::set( Vector3 value )
{
	mHalfExtents = value;
	mHasUpdate = true;
}