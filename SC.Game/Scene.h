#pragma once

namespace SC::Game
{
	ref class GameObject;
	ref class Camera;
	ref class MeshRenderer;
	ref class Light;
	ref class Collider;

	/// <summary>
	/// 게임의 한 장면을 표현합니다.
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
		/// <see cref="Scene"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Scene();
		~Scene();
		!Scene();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> 인터페이스에서 구현 됨.) 컬렉션 전체를 반복하는 열거자를 반환합니다.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<GameObject^>^ GetEnumerator();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 항목을 추가합니다.
		/// </summary>
		/// <param name="value"> 추가할 개체를 전달합니다. </param>
		/// <returns> 새 요소를 삽입한 위치를 반환합니다. 실패하였을 경우 -1을 반환합니다. </returns>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void Add( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 항목을 모두 제거합니다.
		/// </summary>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void Clear();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 항목이 존재하는지 여부를 확인합니다.
		/// </summary>
		/// <param name="value"> 찾을 개체를 전달합니다. </param>
		/// <returns> 개체가 리스트에 있으면 true, 그렇지 않다면 false를 반환합니다. </returns>
		virtual bool Contains( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 인덱스부터 시작하여 요소를 지정한 배열에 복사합니다.
		/// </summary>
		/// <param name="array"> 복사 대상 배열 포인터입니다. 충분한 크기가 준비되어야 합니다. </param>
		/// <param name="index"> 복사가 시작되는 인덱스입니다. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>가 nullptr인 경우 발생합니다. </exception>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>가 0보다 작거나 배열의 크기보다 크거나 같을 경우 경우 발생합니다. </exception>
		virtual void CopyTo( cli::array<GameObject^>^ array, int index );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 인덱스부터 시작하여 요소를 지정한 배열에 복사합니다.
		/// </summary>
		/// <param name="array"> 복사 대상 배열 포인터입니다. 충분한 크기가 준비되어야 합니다. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>가 nullptr인 경우 발생합니다. </exception>
		void CopyTo( cli::array<GameObject^>^ array )
		{
			CopyTo( array, 0 );
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 항목의 인덱스를 검색합니다.
		/// </summary>
		/// <param name="value"> 찾을 개체를 전달합니다. </param>
		/// <returns> 목록에 개체가 존재하면 개체의 인덱스를, 그렇지 않다면 -1을 반환합니다. </returns>
		virtual int IndexOf( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 리스트에 새 요소를 지정한 인덱스에 삽입합니다.
		/// </summary>
		/// <param name="index"> 삽입할 인덱스를 전달합니다. </param>
		/// <param name="value"> 삽입할 개체를 전달합니다. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>가 0보다 작거나 배열의 크기보다 클 경우 경우 발생합니다. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void Insert( int index, GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 리스트에서 제일 처음 발견되는 특정 개체를 제거합니다.
		/// </summary>
		/// <param name="value"> 제거할 개체를 전달합니다. </param>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual bool Remove( GameObject^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 리스트에서 제일 처음 발견되는 특정 개체를 제거합니다.
		/// </summary>
		/// <param name="index"> 제거할 항목의 인덱스를 전달합니다. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>가 0보다 작거나 배열의 크기보다 크거나 같을 경우 경우 발생합니다. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void RemoveAt( int index );

		/// <summary>
		/// 특정 항목의 인덱스를 검색합니다.
		/// </summary>
		/// <param name="xName"> 찾을 개체의 이름을 전달합니다. </param>
		/// <returns> 목록에 개체가 존재하면 개체의 인덱스를, 그렇지 않다면 -1을 반환합니다. </returns>
		int IndexOf( System::String^ xName );

		/// <summary>
		/// 장면에 존재하는 모든 개체에 대한 Update를 수행합니다.
		/// </summary>
		virtual void Update();

		/// <summary>
		/// 장면에 존재하는 모든 개체에 대한 FixedUpdate를 수행합니다.
		/// </summary>
		virtual void FixedUpdate();

		/// <summary>
		/// 장면 불러오기 작업을 재정의합니다.
		/// </summary>
		/// <param name="arg"> 불러오기 매개변수를 전달합니다. </param>
		virtual void Load( System::Object^ arg ) = 0;

		/// <summary>
		/// 장면 해제 작업을 재정의합니다.
		/// </summary>
		virtual void Unload() = 0;

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 포함된 요소 수를 가져옵니다.
		/// </summary>
		property int Count
		{
			virtual int get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 크기가 고정되어 있는지 여부를 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsFixedSize
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 해당 개체가 읽기 전용 개체인지 여부를 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsReadOnly
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 지정한 인덱스에 있는 요소를 설정하거나 가져옵니다.
		/// </summary>
		property GameObject^ default[int]
		{
			virtual GameObject^ get( int index );
			virtual void set( int index, GameObject^ value );
		}
	};
}