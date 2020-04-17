using namespace SC;
using namespace SC::Game;

using namespace System;

using namespace physx;

namespace
{
	PxDefaultAllocator gDefaultAllocator;
	PxDefaultErrorCallback gDefaultErrorCallback;
}

inline void OnDisposing1()
{
	Physics::OnDisposing();
}

void Physics::OnDisposing()
{
	if ( mDefaultMat )
	{
		mDefaultMat->release();
		mDefaultMat = nullptr;
	}

	if ( mCudaManager )
	{
		mCudaManager->release();
		mCudaManager = nullptr;
	}

	if ( mDispatcher )
	{
		mDispatcher->release();
		mDispatcher = nullptr;
	}

	// ������ �÷����� �񵿱⼺�� ����
	// �� ��ü�� �������� �ʽ��ϴ�.
	/*
	if ( mCooking )
	{
		mCooking->release();
		mCooking = nullptr;
	}

	if ( mPhysics )
	{
		mPhysics->release();
		mPhysics = nullptr;
	}

	if ( mPVD )
	{
		mPVD->release();
		mPVD = nullptr;
	}

	// PVD Transport ��ü�� PVD�� ������ �� �����Ǿ�� �մϴ�.
	if ( mPVDTransport )
	{
		mPVDTransport->release();
		mPVDTransport = nullptr;
	}

	if ( mFoundation )
	{
		mFoundation->release();
		mFoundation = nullptr;
	}
	*/
}

void Physics::Initialize()
{
	App::Disposing.push_front( OnDisposing1 );

	// PhysX �Ŀ�̼� ��ü�� �ʱ�ȭ�մϴ�.
	mFoundation = PxCreateFoundation( PX_PHYSICS_VERSION, gDefaultAllocator, gDefaultErrorCallback );
	if ( !mFoundation ) throw gcnew Exception( "Physics.Initialize(): PxCreateFoundation() �Լ����� PxFoundation ��ü�� �����ϴ� �� �����Ͽ����ϴ�." );

#if defined( _DEBUG )
	// ����� ��� ������ ��� Physics Visual Debugger ��ü�� �����մϴ�.
	mPVD = PxCreatePvd( *mFoundation );
	mPVDTransport = PxDefaultPvdSocketTransportCreate( "localhost", 5425, 10000 );
	mPVD->connect( *mPVDTransport, PxPvdInstrumentationFlag::eALL );
#endif

	// PhysX ��ġ ��ü�� �����մϴ�.
	mPhysics = PxCreatePhysics( PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale() );
	if ( !mPhysics ) throw gcnew Exception( "Physics.Initialize(): PxCreatePhysics() �Լ����� PxPhysics ��ü�� �����ϴ� �� �����Ͽ����ϴ�." );

	// PhysX ��ŷ ��ü�� �����մϴ�.
	mCooking = PxCreateCooking( PX_PHYSICS_VERSION, *mFoundation, PxCookingParams( PxTolerancesScale() ) );
	if ( !mCooking ) throw gcnew Exception( "Physics.Initialize(): PxCreateCooking() �Լ����� PxCooking ��ü�� �����ϴ� �� �����Ͽ����ϴ�." );

	// PhysX �۾� Dispatcher ��ü�� �����մϴ�.
	mDispatcher = PxDefaultCpuDispatcherCreate( 8 );
	mCudaManager = PxCreateCudaContextManager( *mFoundation, PxCudaContextManagerDesc() );

	// ���� ���� ���� ��ü�� �����մϴ�.
	mDefaultMat = mPhysics->createMaterial( 0.5f, 0.5f, 0.6f );
}