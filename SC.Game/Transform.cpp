using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

#pragma unmanaged
void Transform_Constants::Initialize()
{
	auto identity = XMMatrixIdentity();
	XMStoreFloat4x4( &World, identity );
	XMStoreFloat4x4( &WorldInvTranspose, identity );
}
#pragma managed

void Transform::CreateBuffer()
{
	if ( !mConstants )
	{
		mConstants = HeapAllocator::Alloc( sizeof( Transform_Constants ) ).Detach();
	}
}

void Transform::Update()
{
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
	auto prevPos = Position;
	auto prevScale = Scale;
	auto prevRot = Rotation;

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

	Position = prevPos;
	Scale = prevScale;
	Rotation = prevRot;
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
}

Matrix4x4 Transform::LocalWorld::get()
{
	return Matrix4x4::CreateScale( mLocalScale ) * Matrix4x4::CreateFromQuaternion( mLocalRotation ) * Matrix4x4::CreateTranslation( mLocalPosition );
}

void Transform::LocalWorld::set( Matrix4x4 value )
{
	Matrix4x4::Decompose( value, mLocalScale, mLocalRotation, mLocalPosition );
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
}

Vector3 Transform::LocalPosition::get()
{
	return mLocalPosition;
}

void Transform::LocalPosition::set( Vector3 value )
{
	mLocalPosition = value;
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
}

Vector3 Transform::LocalScale::get()
{
	return mLocalScale;
}

void Transform::LocalScale::set( Vector3 value )
{
	mLocalScale = value;
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
}

Quaternion Transform::LocalRotation::get()
{
	return mLocalRotation;
}

void Transform::LocalRotation::set( Quaternion value )
{
	mLocalRotation = value;
}

Vector3 Transform::Forward::get()
{
	return Vector3::Transform( Vector3::UnitZ, Rotation );
}

void Transform::Forward::set( Vector3 value )
{
	LookTo( value );
}

bool Transform::IsUpdated::get()
{
	throw gcnew NotImplementedException();
}