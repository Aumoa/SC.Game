#pragma once

namespace SC::Game
{
	ref class GameObject;
	ref class Camera;
	ref class MeshRenderer;
	ref class Light;
	ref class Collider;

	/// <summary>
	/// ������ �� ����� ǥ���մϴ�.
	/// </summary>
	public ref class Scene abstract : public System::Collections::Generic::IList<GameObject^>
	{
	internal:
		using MyList = System::Collections::Generic::List<GameObject^>;

		Diagnostics::StepTimer^ mUpdateTimer;
		Diagnostics::StepTimer^ mFixedUpdateTimer;

		System::Collections::Generic::List<GameObject^>^ mGameObjects;

		System::Collections::Generic::List<GameObject^>^ mSceneGraph;
		System::Collections::Generic::List<Camera^>^ mSceneCameras;
		System::Collections::Generic::List<MeshRenderer^>^ mSceneMeshRenderers;
		System::Collections::Generic::List<Light^>^ mSceneLights;
		System::Collections::Generic::List<Collider^>^ mSceneColliders;
		SkinnedMeshRendererQueue* mSkinnedMeshRendererQueue = nullptr;

		System::Collections::Generic::IDictionary<int, MyList^>^ mThreadSceneGraph;

		ContactCallback* mSimulationEventCallback = nullptr;
		physx::PxScene* mPxScene = nullptr;
		bool mFetchResults = true;
		bool mFixedUpdate = false;

	private:
		virtual System::Collections::IEnumerator^ GetEnumerator2() sealed = System::Collections::IEnumerable::GetEnumerator;
		void PopulateSceneGraph();
		void ReadComponent( GameObject^ gameObject );
		void IncludeChilds( GameObject^ gameObject, int thread );
		void UpdateSpecialComponents();

	internal:
		bool mSceneUpdated = true;

		void UpdateThread( MyList^ list );

	public:
		/// <summary>
		/// <see cref="Scene"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Scene();
		~Scene();
		!Scene();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> �������̽����� ���� ��.) �÷��� ��ü�� �ݺ��ϴ� �����ڸ� ��ȯ�մϴ�.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<GameObject^>^ GetEnumerator();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) �׸��� �߰��մϴ�.
		/// </summary>
		/// <param name="value"> �߰��� ��ü�� �����մϴ�. </param>
		/// <returns> �� ��Ҹ� ������ ��ġ�� ��ȯ�մϴ�. �����Ͽ��� ��� -1�� ��ȯ�մϴ�. </returns>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void Add( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) �׸��� ��� �����մϴ�.
		/// </summary>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void Clear();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �׸��� �����ϴ��� ���θ� Ȯ���մϴ�.
		/// </summary>
		/// <param name="value"> ã�� ��ü�� �����մϴ�. </param>
		/// <returns> ��ü�� ����Ʈ�� ������ true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�. </returns>
		virtual bool Contains( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �ε������� �����Ͽ� ��Ҹ� ������ �迭�� �����մϴ�.
		/// </summary>
		/// <param name="array"> ���� ��� �迭 �������Դϴ�. ����� ũ�Ⱑ �غ�Ǿ�� �մϴ�. </param>
		/// <param name="index"> ���簡 ���۵Ǵ� �ε����Դϴ�. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>�� nullptr�� ��� �߻��մϴ�. </exception>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>�� 0���� �۰ų� �迭�� ũ�⺸�� ũ�ų� ���� ��� ��� �߻��մϴ�. </exception>
		virtual void CopyTo( cli::array<GameObject^>^ array, int index );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �ε������� �����Ͽ� ��Ҹ� ������ �迭�� �����մϴ�.
		/// </summary>
		/// <param name="array"> ���� ��� �迭 �������Դϴ�. ����� ũ�Ⱑ �غ�Ǿ�� �մϴ�. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>�� nullptr�� ��� �߻��մϴ�. </exception>
		void CopyTo( cli::array<GameObject^>^ array )
		{
			CopyTo( array, 0 );
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �׸��� �ε����� �˻��մϴ�.
		/// </summary>
		/// <param name="value"> ã�� ��ü�� �����մϴ�. </param>
		/// <returns> ��Ͽ� ��ü�� �����ϸ� ��ü�� �ε�����, �׷��� �ʴٸ� -1�� ��ȯ�մϴ�. </returns>
		virtual int IndexOf( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ����Ʈ�� �� ��Ҹ� ������ �ε����� �����մϴ�.
		/// </summary>
		/// <param name="index"> ������ �ε����� �����մϴ�. </param>
		/// <param name="value"> ������ ��ü�� �����մϴ�. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>�� 0���� �۰ų� �迭�� ũ�⺸�� Ŭ ��� ��� �߻��մϴ�. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void Insert( int index, GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ����Ʈ���� ���� ó�� �߰ߵǴ� Ư�� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="value"> ������ ��ü�� �����մϴ�. </param>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual bool Remove( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ����Ʈ���� ���� ó�� �߰ߵǴ� Ư�� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="index"> ������ �׸��� �ε����� �����մϴ�. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>�� 0���� �۰ų� �迭�� ũ�⺸�� ũ�ų� ���� ��� ��� �߻��մϴ�. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void RemoveAt( int index );

		/// <summary>
		/// Ư�� �׸��� �ε����� �˻��մϴ�.
		/// </summary>
		/// <param name="xName"> ã�� ��ü�� �̸��� �����մϴ�. </param>
		/// <returns> ��Ͽ� ��ü�� �����ϸ� ��ü�� �ε�����, �׷��� �ʴٸ� -1�� ��ȯ�մϴ�. </returns>
		int IndexOf( System::String^ xName );

		/// <summary>
		/// ��鿡 �����ϴ� ��� ��ü�� ���� Update�� �����մϴ�.
		/// </summary>
		virtual void Update();

		/// <summary>
		/// ��鿡 �����ϴ� ��� ��ü�� ���� FixedUpdate�� �����մϴ�.
		/// </summary>
		virtual void FixedUpdate();

		/// <summary>
		/// ��� �ҷ����� �۾��� �������մϴ�.
		/// </summary>
		/// <param name="arg"> �ҷ����� �Ű������� �����մϴ�. </param>
		virtual void Load( System::Object^ arg ) = 0;

		/// <summary>
		/// ��� ���� �۾��� �������մϴ�.
		/// </summary>
		virtual void Unload() = 0;

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ���Ե� ��� ���� �����ɴϴ�.
		/// </summary>
		property int Count
		{
			virtual int get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ũ�Ⱑ �����Ǿ� �ִ��� ���θ� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsFixedSize
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) �ش� ��ü�� �б� ���� ��ü���� ���θ� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsReadOnly
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ������ �ε����� �ִ� ��Ҹ� �����ϰų� �����ɴϴ�.
		/// </summary>
		property GameObject^ default[int]
		{
			virtual GameObject^ get( int index );
			virtual void set( int index, GameObject^ value );
		}
	};
}