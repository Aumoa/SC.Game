using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace physx;

Collider::Collider() : Component()
{

}

void Collider::CloneAs( Collider^ pCollider )
{
	pCollider->mCenter = mCenter;
	pCollider->mRotation = mRotation;
	pCollider->mHasUpdate = mHasUpdate;
}

void Collider::AttachToActor( PxRigidActor* pActor )
{
	ReleaseShape();
	mActor = pActor;
	mHasUpdate = true;
}

void Collider::Update()
{
	if ( mHasUpdate && mActor )
	{
		PxTransform localPose;
		Assign( localPose.p, mCenter * Transform->Scale );
		Assign( localPose.q, mRotation );
		if ( mShape && !mMaterialUpdated )
		{
			mShape->setGeometry( *mGeometry );
		}
		else
		{
			PxMaterial* mat = mMaterial ? mMaterial->mMaterial : nullptr;
			if ( mat == nullptr )
			{
				mat = Physics::mDefaultMat;
			}

			PxShapeFlag::Enum shapeType = mIsTrigger ? PxShapeFlag::eTRIGGER_SHAPE : PxShapeFlag::eSIMULATION_SHAPE;

			mShape = PxRigidActorExt::createExclusiveShape( *mActor, *mGeometry, *mat, PxShapeFlag::eSCENE_QUERY_SHAPE | shapeType );
			mShape->userData = new gcroot<Collider^>( this );
		}
		mShape->setLocalPose( localPose );

		mHasUpdate = false;
		mMaterialUpdated = false;
	}
}

void Collider::ReleaseShape()
{
	if ( mShape && !mActor )
	{
		delete ( gcroot<Collider^>* )mShape->userData;
		mShape->userData = nullptr;
		mShape->release();
		mShape = nullptr;
	}
}

Collider::~Collider()
{
	this->!Collider();
}

Collider::!Collider()
{
	if ( mGeometry )
	{
		delete mGeometry;
		mGeometry = nullptr;
	}

	ReleaseShape();
}

Vector3 Collider::Center::get()
{
	return mCenter;
}

void Collider::Center::set( Vector3 value )
{
	mCenter = value;
	mHasUpdate = true;
}

Quaternion Collider::Rotation::get()
{
	return mRotation;
}

void Collider::Rotation::set( Quaternion value )
{
	mRotation = value;
	mHasUpdate = true;
}

bool Collider::IsTrigger::get()
{
	return mIsTrigger;
}

void Collider::IsTrigger::set( bool value )
{
	if ( mShape )
	{
		mShape->setFlag( PxShapeFlag::eSIMULATION_SHAPE, !value );
		mShape->setFlag( PxShapeFlag::eTRIGGER_SHAPE, value );
	}
	mIsTrigger = value;
	mHasUpdate = true;
}

PhysicsMaterial^ Collider::Material::get()
{
	return mMaterial;
}

void Collider::Material::set( PhysicsMaterial^ value )
{
	mMaterial = value;
	mHasUpdate = true;
	mMaterialUpdated = true;
}