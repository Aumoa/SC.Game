using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace physx;

#pragma unmanaged
void Transform_Constants::Initialize()
{
	auto identity = XMMatrixIdentity();
	XMStoreFloat4x4( &World, identity );
	XMStoreFloat4x4( &WorldInvTranspose, identity );
}
#pragma managed

void Transform::WriteRigid( Vector3 p, Quaternion q )
{
	if ( mGameObject->mRigidbody )
	{
		PxTransform gp;
		Assign( gp.p, p );
		Assign( gp.q, q );
		mGameObject->mRigidbody->setGlobalPose( gp );
	}
}

void Transform::CreateBuffer()
{
	if ( !mConstants )
	{
		mConstants = HeapAllocator::Alloc( sizeof( Transform_Constants ) ).Detach();
	}
}

void Transform::Update()
{
	if ( IsUpdated )
	{
		// 리지드바디가 존재할 경우 물리 계산이 완료된 리지드바디에서 위치와 회전 벡터를 가져옵니다.
		if ( mGameObject->mRigidbody && !mGameObject->mIsStaticRigid )
		{
			auto gp = mGameObject->mRigidbody->getGlobalPose();
			Vector3 pos;
			Quaternion quat;
			Assign( pos, gp.p );
			Assign( quat, gp.q );

			// 리지드바디의 정보를 트랜스폼 정보로 가져옵니다.
			Vector3 identity1 = Vector3::Zero;
			if ( mParent )
			{
				identity1 = mParent->Position;
			}
			mLocalPosition = Vector3::operator-( pos, identity1 );
			Quaternion identity2 = Quaternion::Identity;
			if ( mParent )
			{
				identity2 = mParent->Rotation;
			}
			mLocalRotation = quat * Quaternion::Conjugate( identity2 );
		}

		if ( mConstants )
		{
			Matrix4x4 world = World;
			Matrix4x4 invert;
			Matrix4x4::Invert( world, invert );
			auto worldInvTrp = Matrix4x4::Transpose( invert );

			Assign( mFrameResource->World, world );
			Assign( mFrameResource->WorldInvTranspose, worldInvTrp );

			auto block = mConstants->Map();
			memcpy( block, mFrameResource, sizeof( *mFrameResource ) );
			mConstants->Unmap();
		}
	}
}

Transform::Transform()
{
	mFrameResource = new Transform_Constants;
	mFrameResource->Initialize();
	mLocalScale = Vector3::One;
	mLocalRotation = Quaternion::Identity;
}

Transform::~Transform()
{
	this->!Transform();
}

Transform::!Transform()
{
	if ( mConstants )
	{
		mConstants->Release();
		mConstants = nullptr;
	}

	if ( mFrameResource )
	{
		delete mFrameResource;
		mFrameResource = nullptr;
	}
}

Object^ Transform::Clone()
{
	auto clone = gcnew Transform();

	clone->mLocalPosition = mLocalPosition;
	clone->mLocalScale = mLocalScale;
	clone->mLocalRotation = mLocalRotation;

	*clone->mFrameResource = *mFrameResource;

	return clone;
}

void Transform::LookAt( Vector3 target, Vector3 up )
{
	Vector3 pos = Position;
	Vector3 dir = Vector3::Normalize( Vector3::Subtract( target, pos ) );
	Vector3 right = Vector3::Normalize( Vector3::Cross( up, dir ) );
	up = Vector3::Normalize( Vector3::Cross( dir, right ) );

	Matrix4x4 world = Matrix4x4::Identity;

	world.M11 = right.X;
	world.M12 = right.Y;
	world.M13 = right.Z;

	world.M21 = up.X;
	world.M22 = up.Y;
	world.M23 = up.Z;

	world.M31 = dir.X;
	world.M32 = dir.Y;
	world.M33 = dir.Z;

	world.Translation = pos;

	World = world;
	mBufferUpdated = true;
}

void Transform::LookTo( Vector3 direction, Vector3 up )
{
	LookAt( Position + direction, up );
}

void Transform::LocalLookAt( Vector3 target, Vector3 up )
{
	Vector3 pos = LocalPosition;
	Vector3 dir = Vector3::Normalize( Vector3::Subtract( target, pos ) );
	Vector3 right = Vector3::Normalize( Vector3::Cross( up, dir ) );
	up = Vector3::Normalize( Vector3::Cross( dir, right ) );

	Matrix4x4 world = Matrix4x4::Identity;

	world.M11 = right.X;
	world.M12 = right.Y;
	world.M13 = right.Z;

	world.M21 = up.X;
	world.M22 = up.Y;
	world.M23 = up.Z;

	world.M31 = dir.X;
	world.M32 = dir.Y;
	world.M33 = dir.Z;

	world.Translation = pos;

	LocalWorld = world;
	mBufferUpdated = true;
}

void Transform::LocalLookTo( Vector3 direction, Vector3 up )
{
	LocalLookAt( LocalPosition + direction, up );
}

Transform^ Transform::Parent::get()
{
	return mParent;
}

void Transform::Parent::set( Transform^ value )
{
	if ( mParent )
	{
		auto index = mParent->mGameObject->mGameObjects->IndexOf( mGameObject );
		if ( index != -1 )
		{
			mParent->mGameObject->mGameObjects->RemoveAt( index );
		}
	}

	mParent = value;

	if ( mParent )
	{
		mParent->mGameObject->mGameObjects->Add( mGameObject );
	}
}

Matrix4x4 Transform::World::get()
{
	auto world = LocalWorld;
	if ( mParent )
	{
		return world * mParent->World;
	}
	else
	{
		return world;
	}
}

void Transform::World::set( Matrix4x4 value )
{
	Matrix4x4 worldInv = Matrix4x4::Identity;
	if ( mParent )
	{
		Matrix4x4::Invert( mParent->World, worldInv );
	}

	auto world = value * worldInv;
	Matrix4x4::Decompose( world, mLocalScale, mLocalRotation, mLocalPosition );

	WriteRigid( Position, Rotation );
	mBufferUpdated = true;
}

Matrix4x4 Transform::LocalWorld::get()
{
	return Matrix4x4::CreateScale( mLocalScale ) * Matrix4x4::CreateFromQuaternion( mLocalRotation ) * Matrix4x4::CreateTranslation( mLocalPosition );
}

void Transform::LocalWorld::set( Matrix4x4 value )
{
	Matrix4x4::Decompose( value, mLocalScale, mLocalRotation, mLocalPosition );
	mBufferUpdated = true;
}

Vector3 Transform::Position::get()
{
	Vector3 identity = Vector3::Zero;
	if ( mParent )
	{
		identity = mParent->Position;
	}
	return identity + mLocalPosition;
}

void Transform::Position::set( Vector3 value )
{
	Vector3 identity = Vector3::Zero;
	if ( mParent )
	{
		identity = mParent->Position;
	}
	mLocalPosition = Vector3::operator-( value, identity );

	WriteRigid( value, Rotation );
	mBufferUpdated = true;
}

Vector3 Transform::LocalPosition::get()
{
	return mLocalPosition;
}

void Transform::LocalPosition::set( Vector3 value )
{
	mLocalPosition = value;
	WriteRigid( Position, Rotation );
	mBufferUpdated = true;
}

Vector3 Transform::Scale::get()
{
	Vector3 identity = Vector3::One;
	if ( mParent )
	{
		identity = mParent->Scale;
	}
	return identity * mLocalScale;
}

void Transform::Scale::set( Vector3 value )
{
	Vector3 identity = Vector3::One;
	if ( mParent )
	{
		identity = mParent->Scale;
	}
	mLocalScale = value / identity;
	mBufferUpdated = true;
}

Vector3 Transform::LocalScale::get()
{
	return mLocalScale;
}

void Transform::LocalScale::set( Vector3 value )
{
	mLocalScale = value;
	mBufferUpdated = true;
}

Quaternion Transform::Rotation::get()
{
	Quaternion identity = Quaternion::Identity;
	if ( mParent )
	{
		identity = mParent->Rotation;
	}
	return identity * mLocalRotation;
}

void Transform::Rotation::set( Quaternion value )
{
	Quaternion identity = Quaternion::Identity;
	if ( mParent )
	{
		identity = mParent->Rotation;
	}
	mLocalRotation = value * Quaternion::Conjugate( identity );

	WriteRigid( Position, value );
	mBufferUpdated = true;
}

Quaternion Transform::LocalRotation::get()
{
	return mLocalRotation;
}

void Transform::LocalRotation::set( Quaternion value )
{
	mLocalRotation = value;
	WriteRigid( Position, Rotation );
	mBufferUpdated = true;
}

Vector3 Transform::Forward::get()
{
	return Vector3::Transform( Vector3::UnitZ, Rotation );
}

void Transform::Forward::set( Vector3 value )
{
	LookTo( value );
	mBufferUpdated = true;
}

bool Transform::IsUpdated::get()
{
	bool v = mBufferUpdated;

	if ( !v && mParent != nullptr )
	{
		v = v || mParent->IsUpdated;
	}

	if ( !v && mGameObject->mRigidbody && !mGameObject->mIsStaticRigid )
	{
		v = true;
	}

	return v;
}