using namespace SC;
using namespace SC::Diagnostics;
using namespace SC::Game;

using namespace System;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

Scene::Scene()
{
	mGameObjects = gcnew List<GameObject^>();

	mSceneGraph = gcnew List<GameObject^>();
	mSceneCameras = gcnew List<Camera^>();
	mSceneMeshRenderers = gcnew List<MeshRenderer^>();
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

		for each ( auto i in mGameObjects )
		{
			IncludeChilds( i );
		}

		mSceneUpdated = false;
	}
}

void Scene::IncludeChilds( GameObject^ gameObject )
{
	mSceneGraph->Add( gameObject );

	if ( auto cam = gameObject->GetComponent<Camera^>(); cam ) mSceneCameras->Add( cam );
	if ( auto meshRenderer = gameObject->GetComponent<MeshRenderer^>(); meshRenderer ) mSceneMeshRenderers->Add( meshRenderer );

	for each ( auto child in gameObject->mGameObjects )
	{
		IncludeChilds( child );
	}
}

IEnumerator<GameObject^>^ Scene::GetEnumerator()
{
	return mGameObjects->GetEnumerator();
}

void Scene::Add( GameObject^ value )
{
	mGameObjects->Add( value );
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

	for each ( auto cam in mSceneCameras )
	{
		cam->Update();
	}

	for each ( auto go in mSceneGraph )
	{
		go->Update();
	}

	mFixedUpdateTimer->Tick( gcnew StepTimerCallbackDelegate( this, &Scene::FixedUpdate ) );
}

void Scene::FixedUpdate()
{
	// FixedUpdate�� ���� Time Ŭ���� ��ü�� �����մϴ�.
	Time::FixedDeltaTime = ( float )mFixedUpdateTimer->ElapsedSeconds;

	for each ( auto go in mSceneGraph )
	{
		go->FixedUpdate();
	}
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