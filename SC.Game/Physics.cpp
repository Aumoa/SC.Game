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

	// 가비지 컬렉터의 비동기성에 의해
	// 이 개체는 제거하지 않습니다.
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

	// PVD Transport 개체는 PVD가 해제된 후 해제되어야 합니다.
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

	// PhysX 파운데이션 개체를 초기화합니다.
	mFoundation = PxCreateFoundation( PX_PHYSICS_VERSION, gDefaultAllocator, gDefaultErrorCallback );
	if ( !mFoundation ) throw gcnew Exception( "Physics.Initialize(): PxCreateFoundation() 함수에서 PxFoundation 개체를 생성하는 데 실패하였습니다." );

#if defined( _DEBUG )
	// 디버그 모드 빌드일 경우 Physics Visual Debugger 개체를 생성합니다.
	mPVD = PxCreatePvd( *mFoundation );
	mPVDTransport = PxDefaultPvdSocketTransportCreate( "localhost", 5425, 10000 );
	mPVD->connect( *mPVDTransport, PxPvdInstrumentationFlag::eALL );
#endif

	// PhysX 장치 개체를 생성합니다.
	mPhysics = PxCreatePhysics( PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale() );
	if ( !mPhysics ) throw gcnew Exception( "Physics.Initialize(): PxCreatePhysics() 함수에서 PxPhysics 개체를 생성하는 데 실패하였습니다." );

	// PhysX 쿠킹 개체를 생성합니다.
	mCooking = PxCreateCooking( PX_PHYSICS_VERSION, *mFoundation, PxCookingParams( PxTolerancesScale() ) );
	if ( !mCooking ) throw gcnew Exception( "Physics.Initialize(): PxCreateCooking() 함수에서 PxCooking 개체를 생성하는 데 실패하였습니다." );

	// PhysX 작업 Dispatcher 개체를 생성합니다.
	mDispatcher = PxDefaultCpuDispatcherCreate( 8 );
	mCudaManager = PxCreateCudaContextManager( *mFoundation, PxCudaContextManagerDesc() );

	// 기초 물리 재질 개체를 생성합니다.
	mDefaultMat = mPhysics->createMaterial( 0.5f, 0.5f, 0.6f );
}