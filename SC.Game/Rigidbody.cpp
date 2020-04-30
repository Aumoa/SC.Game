using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace physx;

Rigidbody::Rigidbody() : Component()
{

}

Object^ Rigidbody::Clone()
{
	auto clone = gcnew Rigidbody();
	return clone;
}

void Rigidbody::AddForce( Vector3 force )
{
	if ( !mRigidbody )
	{
		throw gcnew ComponentDisconnectedException( this );
	}

	PxVec3 pxForce;

	Assign( pxForce, force );

	mRigidbody->addForce( pxForce, PxForceMode::eFORCE );
}

void Rigidbody::MovePosition( Vector3 position )
{
	if ( IsKinematic )
	{
		auto gp = mRigidbody->getGlobalPose();
		Assign( gp.p, position );
		mRigidbody->setKinematicTarget( gp );
	}
	else
	{
		Transform->Position = position;
	}
}

void Rigidbody::WakeUp()
{
	if ( !mRigidbody )
	{
		throw gcnew ComponentDisconnectedException( this );
	}

	mRigidbody->wakeUp();
}

void Rigidbody::Sleep()
{
	if ( !mRigidbody )
	{
		throw gcnew ComponentDisconnectedException( this );
	}

	mRigidbody->putToSleep();
}

Vector3 Rigidbody::Position::get()
{
	if ( !mRigidbody )
	{
		throw gcnew ComponentDisconnectedException( this );
	}

	auto p = mRigidbody->getGlobalPose().p;
	Vector3 pp;
	Assign( pp, p );
	return pp;
}

void Rigidbody::Position::set( Vector3 value )
{
	if ( !mRigidbody )
	{
		throw gcnew ComponentDisconnectedException( this );
	}

	auto gp = mRigidbody->getGlobalPose();
	Assign( gp.p, value );
	mRigidbody->setGlobalPose( gp );
}

Quaternion Rigidbody::Rotation::get()
{
	if ( !mRigidbody )
	{
		throw gcnew ComponentDisconnectedException( this );
	}

	auto q = mRigidbody->getGlobalPose().q;
	Quaternion qq;
	Assign( qq, q );
	return qq;
}

void Rigidbody::Rotation::set( Quaternion value )
{
	if ( !mRigidbody )
	{
		throw gcnew ComponentDisconnectedException( this );
	}

	auto gp = mRigidbody->getGlobalPose();
	Assign( gp.q, value );
	mRigidbody->setGlobalPose( gp );
}

bool Rigidbody::IsKinematic::get()
{
	if ( mRigidbody )
	{
		return mRigidbody->getRigidBodyFlags() & PxRigidBodyFlag::eKINEMATIC;
	}
	else
	{
		throw gcnew ComponentDisconnectedException( this );
	}
}

void Rigidbody::IsKinematic::set( bool value )
{
	if ( mRigidbody )
	{
		mRigidbody->setRigidBodyFlag( PxRigidBodyFlag::eKINEMATIC, value );
		mRigidbody->setRigidBodyFlag( PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES, value );
	}
	else
	{
		throw gcnew ComponentDisconnectedException( this );
	}
}

RigidbodyConstraints Rigidbody::Constraints::get()
{
	auto lockFlags = mRigidbody->getRigidDynamicLockFlags();
	auto constraints = RigidbodyConstraints::None;

	if ( lockFlags & PxRigidDynamicLockFlag::eLOCK_ANGULAR_X )
	{
		constraints = constraints | RigidbodyConstraints::RotationX;
	}

	if ( lockFlags & PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y )
	{
		constraints = constraints | RigidbodyConstraints::RotationY;
	}

	if ( lockFlags & PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z )
	{
		constraints = constraints | RigidbodyConstraints::RotationZ;
	}

	if ( lockFlags & PxRigidDynamicLockFlag::eLOCK_LINEAR_X )
	{
		constraints = constraints | RigidbodyConstraints::PositionX;
	}

	if ( lockFlags & PxRigidDynamicLockFlag::eLOCK_LINEAR_Y )
	{
		constraints = constraints | RigidbodyConstraints::PositionY;
	}

	if ( lockFlags & PxRigidDynamicLockFlag::eLOCK_LINEAR_Z )
	{
		constraints = constraints | RigidbodyConstraints::PositionY;
	}

	return constraints;
}

void Rigidbody::Constraints::set( RigidbodyConstraints value )
{
	PxRigidDynamicLockFlags lockFlags( 0 );
	auto constraints = value;

	if ( ( int )( constraints & RigidbodyConstraints::RotationX ) )
	{
		lockFlags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_X;
	}

	if ( ( int )( constraints & RigidbodyConstraints::RotationY ) )
	{
		lockFlags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y;
	}

	if ( ( int )( constraints & RigidbodyConstraints::RotationZ ) )
	{
		lockFlags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z;
	}

	if ( ( int )( constraints & RigidbodyConstraints::PositionX ) )
	{
		lockFlags |= PxRigidDynamicLockFlag::eLOCK_LINEAR_X;
	}

	if ( ( int )( constraints & RigidbodyConstraints::PositionY ) )
	{
		lockFlags |= PxRigidDynamicLockFlag::eLOCK_LINEAR_Y;
	}

	if ( ( int )( constraints & RigidbodyConstraints::PositionZ ) )
	{
		lockFlags |= PxRigidDynamicLockFlag::eLOCK_LINEAR_Z;
	}

	mRigidbody->setRigidDynamicLockFlags( lockFlags );
}

Vector3 Rigidbody::Velocity::get()
{
	Vector3 velocity;
	Assign( velocity, mRigidbody->getLinearVelocity() );
	return velocity;
}

void Rigidbody::Velocity::set( Vector3 value )
{
	PxVec3 velocity;
	Assign( velocity, value );
	mRigidbody->setLinearVelocity( velocity );
}

float Rigidbody::Mass::get()
{
	return mRigidbody->getMass();
}

void Rigidbody::Mass::set( float value )
{
	mRigidbody->setMass( value );
}

float Rigidbody::Drag::get()
{
	return mRigidbody->getLinearDamping();
}

void Rigidbody::Drag::set( float value )
{
	mRigidbody->setLinearDamping( value );
}

float Rigidbody::AngularDrag::get()
{
	return mRigidbody->getAngularDamping();
}

void Rigidbody::AngularDrag::set( float value )
{
	mRigidbody->setAngularDamping( value );
}