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

	//for each ( auto child in gameObject )
	//{

	//}
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

	mUpdateTimer->Tick( nullptr );
	mFixedUpdateTimer->Tick( gcnew StepTimerCallbackDelegate( this, &Scene::FixedUpdate ) );

	// Update�� ���� Time Ŭ���� ��ü�� �����մϴ�.
	Time::DeltaTime = mUpdateTimer->ElapsedSeconds;
}

void Scene::FixedUpdate()
{
	// FixedUpdate�� ���� Time Ŭ���� ��ü�� �����մϴ�.
	Time::FixedDeltaTime = mFixedUpdateTimer->ElapsedSeconds;
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