using namespace SC;
using namespace SC::Diagnostics;
using namespace SC::Game;

using namespace System;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

using namespace std;
using namespace physx;

#pragma unmanaged
PxFilterFlags ContactReportFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize
)
{
	auto ret = PxDefaultSimulationFilterShader( attributes0, filterData0, attributes1, filterData1, pairFlags, constantBlock, constantBlockSize );

	// all initial and persisting reports for everything, with per-point data
	pairFlags
		= PxPairFlag::eSOLVE_CONTACT
		| PxPairFlag::eDETECT_DISCRETE_CONTACT
		| PxPairFlag::eNOTIFY_TOUCH_FOUND
		| PxPairFlag::eNOTIFY_TOUCH_LOST
		| PxPairFlag::eNOTIFY_CONTACT_POINTS;

	if ( !PxFilterObjectIsTrigger( attributes0 ) && !PxFilterObjectIsTrigger( attributes1 ) )
	{
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_PERSISTS;
	}

	return ret;
}
#pragma managed

Scene::Scene()
{
	mGameObjects = gcnew List<GameObject^>();

	mSceneGraph = gcnew List<GameObject^>();
	mSceneCameras = gcnew List<Camera^>();
	mSceneMeshRenderers = gcnew List<MeshRenderer^>();
	mSceneLights = gcnew List<Light^>();
	mSceneColliders = gcnew List<Collider^>();
	mThreadSceneGraph = gcnew Dictionary<int, MyList^>();
	mSkinnedMeshRendererQueue = new SkinnedMeshRendererQueue();

	mSimulationEventCallback = new ContactCallback();
	auto pxSceneDesc = PxSceneDesc( PxTolerancesScale() );
	pxSceneDesc.gravity = PxVec3( 0.0f, -9.8f, 0.0f );
	pxSceneDesc.cpuDispatcher = Physics::mDispatcher;
	pxSceneDesc.filterShader = ContactReportFilterShader;
	pxSceneDesc.cudaContextManager = Physics::mCudaManager;
	pxSceneDesc.simulationEventCallback = mSimulationEventCallback;
	pxSceneDesc.staticKineFilteringMode = PxPairFilteringMode::eSUPPRESS;
	mPxScene = Physics::mPhysics->createScene( pxSceneDesc );
}

Scene::~Scene()
{
	this->!Scene();
}

Scene::!Scene()
{
	for each ( auto go in mGameObjects )
	{
		go->SetScene( nullptr );
	}

	if ( mSimulationEventCallback )
	{
		delete mSimulationEventCallback;
		mSimulationEventCallback = nullptr;
	}

	if ( mPxScene )
	{
		if ( !mFetchResults )
		{
			mFetchResults = mPxScene->fetchResults( true );
		}

		mPxScene->release();
		mPxScene = nullptr;
	}

	if ( mSkinnedMeshRendererQueue )
	{
		delete mSkinnedMeshRendererQueue;
		mSkinnedMeshRendererQueue = nullptr;
	}
}

System::Collections::IEnumerator^ Scene::GetEnumerator2()
{
	return mGameObjects->GetEnumerator();
}

void Scene::PopulateSceneGraph()
{
	if ( mSceneUpdated )
	{
		mSceneGraph->Clear();
		mSceneCameras->Clear();
		mSceneMeshRenderers->Clear();
		mSceneLights->Clear();
		mSceneColliders->Clear();
		mThreadSceneGraph->Clear();
		mSkinnedMeshRendererQueue->Clear();

		for each ( auto i in mGameObjects )
		{
			IncludeChilds( i, 0 );
		}

		mSkinnedMeshRendererQueue->PushAnimator( nullptr );

		mSceneUpdated = false;
	}
}

void Scene::ReadComponent( GameObject^ gameObject )
{
	if ( auto cam = gameObject->GetComponent<Camera^>(); cam ) mSceneCameras->Add( cam );
	if ( auto meshRenderer = gameObject->GetComponent<MeshRenderer^>(); meshRenderer ) mSceneMeshRenderers->Add( meshRenderer );
	if ( auto meshRenderer = gameObject->GetComponent<SkinnedMeshRenderer^>(); meshRenderer ) mSkinnedMeshRendererQueue->AddRenderer( meshRenderer );
	if ( auto light = gameObject->GetComponent<Light^>(); light ) mSceneLights->Add( light );
	if ( auto collider = gameObject->GetComponent<Collider^>(); collider ) mSceneColliders->Add( collider );
	if ( auto animator = gameObject->GetComponent<Animator^>(); animator ) mSkinnedMeshRendererQueue->PushAnimator( animator );
}

void Scene::IncludeChilds( GameObject^ gameObject, int thread )
{
	mSceneGraph->Add( gameObject );

	ReadComponent( gameObject );

	if ( auto threadDispatcher = gameObject->GetComponent<ThreadDispatcher^>(); threadDispatcher )
	{
		thread = threadDispatcher->ID;
	}

	if ( MyList^ value; mThreadSceneGraph->TryGetValue( thread, value ) )
	{
		value->Add( gameObject );
	}
	else
	{
		auto mylist = gcnew MyList();
		mylist->Add( gameObject );
		mThreadSceneGraph->Add( thread, mylist );
	}

	for each ( auto child in gameObject->mGameObjects )
	{
		IncludeChilds( child, thread );
	}
}

void Scene::UpdateSpecialComponents()
{
	for each ( auto light in mSceneLights )
	{
		light->UpdateBuffer();
	}

	for each ( auto cam in mSceneCameras )
	{
		cam->Update();
	}
}

void Scene::UpdateThread( MyList^ list )
{
	for each ( auto go in list )
	{
		go->Update();
	}

	for each ( auto go in list )
	{
		go->LateUpdate();
	}
}

IEnumerator<GameObject^>^ Scene::GetEnumerator()
{
	return mGameObjects->GetEnumerator();
}

void Scene::Add( GameObject^ value )
{
	mGameObjects->Add( value );
	value->SetScene( this );
	mSceneUpdated = true;
}

void Scene::Clear()
{
	mGameObjects->Clear();
	mSceneUpdated = true;
}

bool Scene::Contains( GameObject^ value )
{
	return mGameObjects->Contains( value );
}

void Scene::CopyTo( cli::array<GameObject^>^ array, int index )
{
	mGameObjects->CopyTo( array, index );
}

int Scene::IndexOf( GameObject^ value )
{
	return mGameObjects->IndexOf( value );
}

void Scene::Insert( int index, GameObject^ value )
{
	mGameObjects->Insert( index, value );
	mSceneUpdated = true;
}

bool Scene::Remove( GameObject^ value )
{
	if ( mGameObjects->Remove( value ) )
	{
		mSceneUpdated = true;
		return true;
	}
	return false;
}

void Scene::RemoveAt( int index )
{
	mGameObjects->RemoveAt( index );
	mSceneUpdated = true;
}

int Scene::IndexOf( String^ xName )
{
	int indexOf = 0;
	for each ( GameObject ^ elem in mGameObjects )
	{
		if ( elem->Name == xName ) return indexOf;
		else indexOf++;
	}

	return -1;
}

namespace
{
	ref class TaskLambda
	{
	public:
		Scene^ Caller;
		Scene::MyList^ Arg;

		void Task()
		{
			Caller->UpdateThread( Arg );
		}
	};
}

void Scene::Update()
{
	// ������ ���� ������Ʈ���� Ÿ�̸Ӹ� �����մϴ�.
	if ( mUpdateTimer == nullptr || mFixedUpdateTimer == nullptr )
	{
		mUpdateTimer = gcnew StepTimer();
		mFixedUpdateTimer = gcnew StepTimer();

		// ���� ���� Ÿ�̸��� ���� �ð� ũ�⸦ �����մϴ�.
		mFixedUpdateTimer->IsFixedTimeStep = true;
		mFixedUpdateTimer->TargetElapsedTicksPerSecond = ApplicationCore::mConfiguration.PhysicsUpdatesPerSecond;
	}

	// ��� �׷����� �ۼ��մϴ�.
	PopulateSceneGraph();

	// Update�� ���� Time Ŭ���� ��ü�� �����մϴ�.
	mUpdateTimer->Tick( nullptr );
	Time::DeltaTime = ( float )mUpdateTimer->ElapsedSeconds;

	if ( !mFetchResults )
	{
		mFetchResults = mPxScene->fetchResults( true );
	}

	// �ö��̴� ��ü�� ������Ʈ�մϴ�.
	for each ( auto collider in mSceneColliders )
	{
		collider->Update();
	}

	// ���� ������Ʈ�� �����մϴ�.
	if ( mThreadSceneGraph->Count != 0 )
	{
		auto tasks = gcnew cli::array<Task^>( mThreadSceneGraph->Count - 1 );
		int i = 0;
		for each ( auto list in mThreadSceneGraph )
		{
			if ( list.Key != 0 )
			{
				auto lambda = gcnew TaskLambda();
				lambda->Caller = this;
				lambda->Arg = list.Value;
				tasks[i++] = Task::Run( gcnew Action( lambda, &TaskLambda::Task ) );
			}
		}
		UpdateThread( mThreadSceneGraph[0] );

		Task::WaitAll( tasks );
	}

	mFixedUpdateTimer->Tick( gcnew StepTimerCallbackDelegate( this, &Scene::FixedUpdate ) );

	// Ư�� ������Ʈ�� ������Ʈ�մϴ�.
	UpdateSpecialComponents();

	// ��� Ʈ�������� ���� ���·� �����մϴ�.
	for each ( auto go in mSceneGraph )
	{
		go->mTransform->mBufferUpdated = false;
	}
}

void Scene::FixedUpdate()
{
	// FixedUpdate�� ���� Time Ŭ���� ��ü�� �����մϴ�.
	Time::FixedDeltaTime = ( float )mFixedUpdateTimer->ElapsedSeconds;

	for each ( auto pair in mSkinnedMeshRendererQueue->mSkinnedPair )
	{
		pair.pAnimator->FixedUpdate();
	}

	for each ( auto go in mSceneGraph )
	{
		go->FixedUpdate();
	}

	mPxScene->simulate( 1.0f / ApplicationCore::mConfiguration.PhysicsUpdatesPerSecond );
	mFetchResults = mPxScene->fetchResults( false );
}

int Scene::Count::get()
{
	return mGameObjects->Count;
}

bool Scene::IsFixedSize::get()
{
	return false;
}

bool Scene::IsReadOnly::get()
{
	return false;
}

GameObject^ Scene::default::get( int index )
{
	return mGameObjects[index];
}

void Scene::default::set( int index, GameObject ^ value )
{
	mGameObjects[index] = value;
}