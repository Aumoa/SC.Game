using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;

bool GameObject::OnComponentAdd( Component^ component )
{
	if ( mSceneRef && component->GetType() == Camera::typeid )
	{
		mSceneRef->mSceneUpdated = true;
	}

	else if ( component->GetType() == MeshRenderer::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}

		mTransform->CreateBuffer();
	}

	return true;
}

void GameObject::SetScene( Scene^ sceneRef )
{
	if ( sceneRef )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}

		mSceneRef = sceneRef;

		for each ( auto go in mGameObjects )
		{
			go->SetScene( sceneRef );
		}

		sceneRef->mSceneUpdated = true;
	}
}

void GameObject::Update()
{
	auto behaviour = Behaviour::typeid;

	mTransform->Update();

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->InternalUpdate();
		}
	}
}

void GameObject::FixedUpdate()
{
	auto behaviour = Behaviour::typeid;

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->FixedUpdate();
		}
	}
}

GameObject::GameObject( String^ xName )
{
	mName = xName;
	mTransform = gcnew Game::Transform();
	mTransform->mGameObject = this;

	mComponents = gcnew List<Component^>();
	mGameObjects = gcnew List<GameObject^>();
}

Object^ GameObject::Clone()
{
	auto clone = gcnew GameObject( mName + L" Clone" );

	for each ( auto gameObject in mGameObjects )
	{
		clone->mGameObjects->Add( ( GameObject^ )gameObject->Clone() );
	}

	for each ( auto component in mComponents )
	{
		clone->mComponents->Add( ( Component^ )component->Clone() );
	}

	return clone;
}

generic< class T > where T : Component, gcnew()
T GameObject::AddComponent()
{
	if ( T::typeid == Game::Transform::typeid ) return T();
	else
	{
		auto component = gcnew T();
		component->mGameObject = this;

		if ( OnComponentAdd( component ) )
			mComponents->Add( component );
		else
			return T();

		return component;
	}
}

generic< class T > where T : Component, gcnew()
T GameObject::GetComponent()
{
	auto type = T::typeid;

	if ( type == Game::Transform::typeid ) return safe_cast< T >( mTransform );
	else
	{
		T candidate = T();

		for each ( auto component in mComponents )
		{
			auto right = component->GetType();

			if ( type == right )
			{
				return ( T )component;
			}

			else if ( candidate == nullptr && type->IsAssignableFrom( right ) )
			{
				candidate = ( T )component;
			}
		}

		return candidate;
	}
}

generic< class T > where T : Component, gcnew()
bool GameObject::RemoveComponent()
{
	auto type = T::typeid;

	if ( type == Game::Transform::typeid ) return false;
	else
	{
		int candidate = -1;

		for ( int i = 0; i < mComponents->Count; ++i )
		{
			auto right = mComponents[i]->GetType();

			if ( type == right )
			{
				candidate = i;
				break;
			}

			else if ( candidate == -1 && type->IsAssignableFrom( right ) )
			{
				candidate = i;
			}
		}

		if ( candidate != -1 )
		{
			mComponents->RemoveAt( candidate );
			return true;
		}

		return false;
	}
}

generic< class T > where T : Component, gcnew()
T GameObject::GetComponentInChildren()
{
	throw gcnew NotImplementedException();
}

generic< class T > where T : Component, gcnew()
IList<T>^ GameObject::GetComponentsInChildren()
{
	throw gcnew NotImplementedException();
}

String^ GameObject::Name::get()
{
	return mName;
}

Transform^ GameObject::Transform::get()
{
	return mTransform;
}