#pragma once

namespace SC::Game
{
	ref class Component;
	ref class Transform;
	ref class CharacterController;

	delegate void MeshChangedDelegate();

	/// <summary>
	/// ��鿡 ���Ե� �� �ִ�, ���� ���迡�� ǥ���Ǵ� ��� ��ü�� ���� �������̽��� �����մϴ�.
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
		/// <see cref="GameObject"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü�� �ĺ� �̸��� �����մϴ�. </param>
		GameObject( System::String^ xName );
		~GameObject();
		!GameObject();

		/// <summary>
		/// (<see cref="System::ICloneable"/> �������̽����� ���� ��.) ���� ��ü�� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		virtual System::Object^ Clone();

		/// <summary>
		/// ��ü�� Ȯ�� ������Ʈ�� �߰��մϴ�.
		/// </summary>
		/// <typeparam name="T"> �߰��� Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ �߰��� �����Ͽ��� ��� �߰��� ������Ʈ��, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component, gcnew()
			T AddComponent();

		/// <summary>
		/// ��ü�� ���Ե� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ������ ��� ������Ʈ ��ü��, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			T GetComponent();

		/// <summary>
		/// ��ü�� ���Ե� Ȯ�� ������Ʈ�� �����մϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ ���ſ� �����Ͽ��� ��� <c>true</c>��, �׷��� ���� ��� <c>false</c>�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			bool RemoveComponent();

		/// <summary>
		/// ���� �켱 Ž�� ��带 ����Ͽ� �ڽ��� ������ ���� ������Ʈ���� ���� ó������ �߰��ϴ� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ��� ��ü���� �ϳ� �̻� ������ ��� ������Ʈ ��ü��, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			T GetComponentInChildren();

		/// <summary>
		/// �ڽ��� ������ ���� ������Ʈ���� �߰��ϴ� ��� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ��� ��ü���� �ϳ� �̻� ������ ��� ������Ʈ ��ü �����, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			System::Collections::Generic::IList<T>^ GetComponentsInChildren();

		/// <summary>
		/// ��ü�� ���� ��ü�� �����ɴϴ�.
		/// </summary>
		GameObject^ GetChild( int index );

		/// <summary>
		/// ��ü�� ��ȯ ��ü�� �����ɴϴ�.
		/// </summary>
		property Game::Transform^ Transform
		{
			Game::Transform^ get();
		}

		/// <summary>
		/// ��ü�� ���� ��ü ������ �����ɴϴ�.
		/// </summary>
		property int NumChilds
		{
			int get();
		}

		/// <summary>
		/// ��ü�� �±׸� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Tag Tag
		{
			Game::Tag get();
			void set( Game::Tag value );
		}
	};
}