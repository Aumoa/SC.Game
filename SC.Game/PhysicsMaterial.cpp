using namespace SC;
using namespace SC::Game;

using namespace SC;
using namespace SC::Game;

PhysicsMaterial::PhysicsMaterial( System::String^ xName ) : Asset( xName )
{
	mMaterial = Physics::mPhysics->createMaterial( 0.5f, 0.5f, 0.6f );
}

PhysicsMaterial::~PhysicsMaterial()
{
	this->!PhysicsMaterial();
}

PhysicsMaterial::!PhysicsMaterial()
{
	if ( mMaterial )
	{
		mMaterial->release();
		mMaterial = nullptr;
	}
}

float PhysicsMaterial::StaticFriction::get()
{
	return mStaticFriction;
}

void PhysicsMaterial::StaticFriction::set( float value )
{
	mStaticFriction = value;
	mMaterial->setStaticFriction( value );
}

float PhysicsMaterial::DynamicFriction::get()
{
	return mDynamicFriction;
}

void PhysicsMaterial::DynamicFriction::set( float value )
{
	mDynamicFriction = value;
	mMaterial->setDynamicFriction( value );
}

float PhysicsMaterial::Restitution::get()
{
	return mRestitution;
}

void PhysicsMaterial::Restitution::set( float value )
{
	mRestitution = value;
	mMaterial->setRestitution( value );
}