using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace physx;

void SphereCollider::Update()
{
	if ( mHasUpdate || Transform->IsUpdated )
	{
		auto scale = Transform->Scale;

		auto geo = static_cast< PxSphereGeometry* >( mGeometry );
		geo->radius = ( PxReal )( mRadius * ( scale.X + scale.Y + scale.Z ) * 0.33333f );
	}

	Collider::Update();
}

SphereCollider::SphereCollider() : Collider()
{
	auto capsuleGeo = new PxSphereGeometry();
	capsuleGeo->radius = 1.0f;

	mGeometry = capsuleGeo;
}

float SphereCollider::Radius::get()
{
	return mRadius;
}

void SphereCollider::Radius::set( float value )
{
	mRadius = value;
	mHasUpdate = true;
}