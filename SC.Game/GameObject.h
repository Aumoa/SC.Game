#pragma once

namespace SC::Game
{
	ref class Component;
	ref class Transform;
	ref class CharacterController;

	delegate void MeshChangedDelegate();

	/// <summary>
	/// 장면에 포함될 수 있는, 게임 세계에서 표현되는 모든 개체의 공통 인터페이스를 제공합니다.
	/// </summary>
	public ref class GameObject : public Asset, public System::ICloneable
	{
	internal:
		Scene^ mSceneRef;

		Game::Transform^ mTransform;
		System::Collections::Generic::List<Component^>^ mComponents;
		System::Collections::Generic::List<GameObject^>^ mGameObjects;

		physx::PxRigidActor* mRigidbody = nullptr;
		bool mIsStaticRigid = false;
		Game::Tag mTag;

		CharacterController^ mController;

	private:
		bool OnComponentAdd( Component^ component );
		void OnComponentRemove( Component^ component );
		void RigidSwap( physx::PxRigidActor* pRigidbody );
		void ControllerSwap( physx::PxController* pController );

	internal:
		void SetScene( Scene^ sceneRef );
		void Update();
		void LateUpdate();
		void FixedUpdate();
		void OnCollisionEnter( Collision collision );
		void OnCollisionExit( Collision collision );
		void OnCollisionStay( Collision collision );
		void OnTriggerEnter( Collider^ collider );
		void OnTriggerExit( Collider^ collider );
		void OnMeshChanged();

	public:
		/// <summary>
		/// <see cref="GameObject"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체의 식별 이름을 전달합니다. </param>
		GameObject( System::String^ xName );
		~GameObject();
		!GameObject();

		/// <summary>
		/// (<see cref="System::ICloneable"/> 인터페이스에서 구현 됨.) 게임 개체의 복사본을 생성하여 반환합니다.
		/// </summary>
		virtual System::Object^ Clone();

		/// <summary>
		/// 개체에 확장 컴포넌트를 추가합니다.
		/// </summary>
		/// <typeparam name="T"> 추가할 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트 추가에 성공하였을 경우 추가된 컴포넌트를, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component, gcnew()
			T AddComponent();

		/// <summary>
		/// 개체에 포함된 확장 컴포넌트를 가져옵니다.
		/// </summary>
		/// <typeparam name="T"> 가져올 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트가 존재할 경우 컴포넌트 개체를, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component
			T GetComponent();

		/// <summary>
		/// 개체에 포함된 확장 컴포넌트를 제거합니다.
		/// </summary>
		/// <typeparam name="T"> 제거할 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트 제거에 성공하였을 경우 <c>true</c>를, 그렇지 않을 경우 <c>false</c>를 반환합니다. </returns>
		generic< class T > where T : Component
			bool RemoveComponent();

		/// <summary>
		/// 깊이 우선 탐색 모드를 사용하여 자신을 포함한 하위 오브젝트에서 가장 처음으로 발견하는 확장 컴포넌트를 가져옵니다.
		/// </summary>
		/// <typeparam name="T"> 가져올 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트가 모든 개체에서 하나 이상 존재할 경우 컴포넌트 개체를, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component
			T GetComponentInChildren();

		/// <summary>
		/// 자신을 포함한 하위 오브젝트에서 발견하는 모든 확장 컴포넌트를 가져옵니다.
		/// </summary>
		/// <typeparam name="T"> 가져올 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트가 모든 개체에서 하나 이상 존재할 경우 컴포넌트 개체 목록을, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component
			System::Collections::Generic::IList<T>^ GetComponentsInChildren();

		/// <summary>
		/// 개체의 하위 개체를 가져옵니다.
		/// </summary>
		GameObject^ GetChild( int index );

		/// <summary>
		/// 개체의 변환 개체를 가져옵니다.
		/// </summary>
		property Game::Transform^ Transform
		{
			Game::Transform^ get();
		}

		/// <summary>
		/// 개체의 하위 개체 개수를 가져옵니다.
		/// </summary>
		property int NumChilds
		{
			int get();
		}

		/// <summary>
		/// 개체의 태그를 설정하거나 가져옵니다.
		/// </summary>
		property Tag Tag
		{
			Game::Tag get();
			void set( Game::Tag value );
		}
	};
}