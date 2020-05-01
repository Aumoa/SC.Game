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
		// 새로운 Dynamic 리지드바디를 생성합니다.
		auto pos = Transform->Position;
		auto quat = Transform->Rotation;

		PxTransform gp;
		Assign( gp.p, pos );
		Assign( gp.q, quat );

		auto pxRigid = Physics::mPhysics->createRigidDynamic( gp );
		RigidSwap( pxRigid->is<PxRigidActor>() );
		mIsStaticRigid = false;

		// 기존 충돌체 컴포넌트가 있을 경우 추가합니다.
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

	else if ( CharacterController::typeid == component->GetType() )
	{
		mController = ( CharacterController^ )component;

		if ( mSceneRef )
		{
			PxExtendedVec3 pos;
			Assign( pos, Transform->Position );

			PxCapsuleControllerDesc capsuleControllerDesc{ };
			capsuleControllerDesc.setToDefault();
			capsuleControllerDesc.radius = mController->mRadius;
			capsuleControllerDesc.height = mController->mHeight;
			capsuleControllerDesc.density = mController->mDensity;
			capsuleControllerDesc.slopeLimit = mController->mSlopeLimit;
			capsuleControllerDesc.material = Physics::mDefaultMat;
			capsuleControllerDesc.stepOffset = mController->mStepOffset;

			mController->mController = mSceneRef->mCharacterControllerManager->createController( capsuleControllerDesc );
			mController->mController->setFootPosition( pos );
		}
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

	else if ( component->GetType() == CharacterController::typeid )
	{
		ControllerSwap( nullptr );
		mController = nullptr;
	}
}

void GameObject::RigidSwap( PxRigidActor* pRigidbody )
{
	if ( mRigidbody )
	{
		if ( mSceneRef )
		{
			// 장면에서 기존 리지드바디를 제거합니다.
			mSceneRef->mPxScene->removeActor( *mRigidbody );
		}

		// 기존의 리지드바디를 제거합니다.
		delete ( gcroot<GameObject^>* )mRigidbody->userData;
		mRigidbody->release();
		mRigidbody = nullptr;
	}

	mRigidbody = pRigidbody;
	mRigidbody->userData = new gcroot<GameObject^>( this );

	// 장면에 새 리지드바디를 추가합니다.
	if ( mSceneRef )
	{
		mSceneRef->mPxScene->addActor( *mRigidbody );
	}
}

void GameObject::ControllerSwap( physx::PxController* pController )
{

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

		if ( mController && !mController->mController )
		{
			PxExtendedVec3 pos;
			Assign( pos, Transform->Position );

			PxCapsuleControllerDesc capsuleControllerDesc{ };
			capsuleControllerDesc.setToDefault();
			capsuleControllerDesc.radius = mController->mRadius;
			capsuleControllerDesc.height = mController->mHeight;
			capsuleControllerDesc.density = mController->mDensity;
			capsuleControllerDesc.slopeLimit = mController->mSlopeLimit;
			capsuleControllerDesc.material = Physics::mDefaultMat;
			capsuleControllerDesc.stepOffset = mController->mStepOffset;

			mController->mController = sceneRef->mCharacterControllerManager->createController( capsuleControllerDesc );
			mController->mController->setFootPosition( pos );
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

void GameObject::OnMeshChanged()
{
	auto meshCollider = GetComponent<MeshCollider^>();
	if ( meshCollider )
	{
		meshCollider->mHasUpdate = true;
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
	auto go = gcnew GameObject( Name + L" Clone" );
	go->Transform->Clone( Transform );

	for each ( auto gameObject in mGameObjects )
	{
		auto clone = ( GameObject^ )gameObject->Clone();
		clone->Transform->Parent = go->Transform;
	}

	for each ( auto component in mComponents )
	{
		auto clone = ( Component^ )component->Clone();
		clone->mGameObject = go;
		go->OnComponentAdd( clone );
		go->mComponents->Add( clone );
	}

	go->mTag = mTag;

	return go;
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
	if ( auto parent = Transform->mParent; parent )
	{
		return parent->Object->Tag | mTag;
	}
	else
	{
		return mTag;
	}
}

void GameObject::Tag::set( Game::Tag value )
{
	mTag = value;
}