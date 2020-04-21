using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;

using namespace physx;

bool GameObject::OnComponentAdd( Component^ component )
{
	if ( component->GetType() == Camera::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}
	}

	else if ( component->GetType() == MeshRenderer::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}

		mTransform->CreateBuffer();
	}

	else if ( component->GetType() == SkinnedMeshRenderer::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}

		mTransform->CreateBuffer();
	}

	else if ( component->GetType() == Animator::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}
	}

	else if ( component->GetType() == Camera::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}
	}

	else if ( component->GetType() == Light::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}
	}

	else if ( component->GetType() == Rigidbody::typeid )
	{
		// ���ο� Dynamic ������ٵ� �����մϴ�.
		auto pos = Transform->Position;
		auto quat = Transform->Rotation;

		PxTransform gp;
		Assign( gp.p, pos );
		Assign( gp.q, quat );

		auto pxRigid = Physics::mPhysics->createRigidDynamic( gp );
		RigidSwap( pxRigid->is<PxRigidActor>() );
		mIsStaticRigid = false;

		// ���� �浹ü ������Ʈ�� ���� ��� �߰��մϴ�.
		auto colliders = GetComponentsInChildren<Collider^>();
		for each ( auto collider in colliders )
		{
			collider->AttachToActor( mRigidbody );
		}

		auto rigidbody = ( Rigidbody^ )component;
		rigidbody->mRigidbody = pxRigid->is<PxRigidDynamic>();
	}

	else if ( Collider::typeid->IsAssignableFrom( component->GetType() ) )
	{
		if ( !mRigidbody )
		{
			PxTransform gp;
			Assign( gp.p, Transform->Position );
			Assign( gp.q, Transform->Rotation );

			auto pRigid = Physics::mPhysics->createRigidStatic( gp );
			RigidSwap( pRigid->is<PxRigidActor>() );
			mIsStaticRigid = true;
		}

		auto pIsCol = safe_cast< Collider^ >( component );
		pIsCol->AttachToActor( mRigidbody );
	}

	return true;
}

void GameObject::OnComponentRemove( Component^ component )
{
	if ( component->GetType() == Camera::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}
	}

	else if ( component->GetType() == MeshRenderer::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}

		mTransform->CreateBuffer();
	}

	else if ( component->GetType() == Camera::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}
	}

	else if ( component->GetType() == Light::typeid )
	{
		if ( mSceneRef )
		{
			mSceneRef->mSceneUpdated = true;
		}
	}

	else if ( component->GetType() == Rigidbody::typeid )
	{
		auto pos = Transform->Position;
		auto quat = Transform->Rotation;

		PxTransform gp;
		Assign( gp.p, pos );
		Assign( gp.q, quat );

		auto pxRigid = Physics::mPhysics->createRigidStatic( gp );
		RigidSwap( pxRigid );
		mIsStaticRigid = true;

		auto colliders = GetComponentsInChildren<Collider^>();
		for each ( auto collider in colliders )
		{
			collider->AttachToActor( pxRigid );
		}
	}
}

void GameObject::RigidSwap( PxRigidActor* pRigidbody )
{
	if ( mRigidbody )
	{
		if ( mSceneRef )
		{
			// ��鿡�� ���� ������ٵ� �����մϴ�.
			mSceneRef->mPxScene->removeActor( *mRigidbody );
		}

		// ������ ������ٵ� �����մϴ�.
		delete ( gcroot<GameObject^>* )mRigidbody->userData;
		mRigidbody->release();
		mRigidbody = nullptr;
	}

	mRigidbody = pRigidbody;
	mRigidbody->userData = new gcroot<GameObject^>( this );

	// ��鿡 �� ������ٵ� �߰��մϴ�.
	if ( mSceneRef )
	{
		mSceneRef->mPxScene->addActor( *mRigidbody );
	}
}

void GameObject::SetScene( Scene^ sceneRef )
{
	if ( mSceneRef )
	{
		if ( mRigidbody )
		{
			mSceneRef->mPxScene->removeActor( *mRigidbody );
		}
		mSceneRef->Remove( this );
	}

	mSceneRef = sceneRef;

	for each ( auto go in mGameObjects )
	{
		go->SetScene( sceneRef );
	}

	if ( sceneRef )
	{
		if ( mRigidbody )
		{
			mSceneRef->mPxScene->addActor( *mRigidbody );
		}
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

void GameObject::LateUpdate()
{
	auto behaviour = Behaviour::typeid;

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->LateUpdate();
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

void GameObject::OnCollisionEnter( Collision collision )
{
	auto behaviour = Behaviour::typeid;

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->OnCollisionEnter( collision );
		}
	}
}

void GameObject::OnCollisionExit( Collision collision )
{
	auto behaviour = Behaviour::typeid;

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->OnCollisionExit( collision );
		}
	}
}

void GameObject::OnCollisionStay( Collision collision )
{
	auto behaviour = Behaviour::typeid;

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->OnCollisionStay( collision );
		}
	}
}

void GameObject::OnTriggerEnter( Collider^ collider )
{
	auto behaviour = Behaviour::typeid;

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->OnTriggerEnter( collider );
		}
	}
}

void GameObject::OnTriggerExit( Collider^ collider )
{
	auto behaviour = Behaviour::typeid;

	for each ( auto comp in mComponents )
	{
		if ( comp->GetType()->IsSubclassOf( behaviour ) )
		{
			auto beh = ( Behaviour^ )comp;
			beh->OnTriggerExit( collider );
		}
	}
}

GameObject::GameObject( String^ xName ) : Asset( xName )
{
	mTransform = gcnew Game::Transform();
	mTransform->mGameObject = this;

	mComponents = gcnew List<Component^>();
	mGameObjects = gcnew List<GameObject^>();
}

GameObject::~GameObject()
{
	this->!GameObject();
}

GameObject::!GameObject()
{
	if ( mRigidbody )
	{
		if ( mSceneRef && mRigidbody )
		{
			mSceneRef->mPxScene->removeActor( *mRigidbody );
		}

		delete ( gcroot<GameObject^>* )mRigidbody->userData;
		mRigidbody->release();
		mRigidbody = nullptr;
	}
}

Object^ GameObject::Clone()
{
	auto clone = gcnew GameObject( Name + L" Clone" );

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

generic< class T > where T : Component
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

generic< class T > where T : Component
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
			OnComponentRemove( mComponents[candidate] );
			mComponents->RemoveAt( candidate );
			return true;
		}

		return false;
	}
}

generic< class T > where T : Component
T GameObject::GetComponentInChildren()
{
	T component = GetComponent<T>();
	if ( component != nullptr ) return component;
	else
	{
		for each ( auto go in mGameObjects )
		{
			component = go->GetComponentInChildren<T>();
			if ( component != nullptr ) return component;
		}
	}

	return component;
}

generic< class T > where T : Component
IList<T>^ GameObject::GetComponentsInChildren()
{
	List<T>^ list = gcnew List<T>();
	auto ttypeid = T::typeid;

	if ( ttypeid == Game::Transform::typeid )
	{
		list->Add( ( T )mTransform );
	}

	for each ( auto component in mComponents )
	{
		auto ctypeid = component->GetType();
		if ( ttypeid == ctypeid || ttypeid->IsAssignableFrom( ctypeid ) )
		{
			list->Add( ( T )component );
		}
	}

	for each ( auto go in mGameObjects )
	{
		auto glist = go->GetComponentsInChildren<T>();
		list->AddRange( glist );
	}

	return list;
}

GameObject^ GameObject::GetChild( int index )
{
	return mGameObjects[index];
}

Transform^ GameObject::Transform::get()
{
	return mTransform;
}

int GameObject::NumChilds::get()
{
	return mGameObjects->Count;
}

Tag GameObject::Tag::get()
{
	return mTag;
}

void GameObject::Tag::set( Game::Tag value )
{
	mTag = value;
}