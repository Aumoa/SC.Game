#pragma once

namespace SC::Game
{
	ref class Component;
	ref class Transform;

	/// <summary>
	/// ��鿡 ���Ե� �� �ִ�, ���� ���迡�� ǥ���Ǵ� ��� ��ü�� ���� �������̽��� �����մϴ�.
	/// </summary>
	public ref class GameObject : public System::ICloneable
	{
	internal:
		System::String^ mName;
		Scene^ mSceneRef;

		Game::Transform^ mTransform;
		System::Collections::Generic::List<Component^>^ mComponents;
		System::Collections::Generic::List<GameObject^>^ mGameObjects;

	private:
		bool OnComponentAdd( Component^ component );

	internal:
		void SetScene( Scene^ sceneRef );
		void Update();
		void FixedUpdate();

	public:
		/// <summary>
		/// <see cref="GameObject"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü�� �ĺ� �̸��� �����մϴ�. </param>
		GameObject( System::String^ xName );

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
		generic< class T > where T : Component, gcnew()
		T GetComponent();

		/// <summary>
		/// ��ü�� ���Ե� Ȯ�� ������Ʈ�� �����մϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ ���ſ� �����Ͽ��� ��� <c>true</c>��, �׷��� ���� ��� <c>false</c>�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component, gcnew()
		bool RemoveComponent();

		/// <summary>
		/// ���� �켱 Ž�� ��带 ����Ͽ� �ڽ��� ������ ���� ������Ʈ���� ���� ó������ �߰��ϴ� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ��� ��ü���� �ϳ� �̻� ������ ��� ������Ʈ ��ü��, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component, gcnew()
		T GetComponentInChildren();

		/// <summary>
		/// �ڽ��� ������ ���� ������Ʈ���� �߰��ϴ� ��� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ��� ��ü���� �ϳ� �̻� ������ ��� ������Ʈ ��ü �����, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component, gcnew()
		System::Collections::Generic::IList<T>^ GetComponentsInChildren();

		/// <summary>
		/// ��ü�� �ĺ� �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}

		/// <summary>
		/// ��ü�� ��ȯ ��ü�� �����ɴϴ�.
		/// </summary>
		property Game::Transform^ Transform
		{
			Game::Transform^ get();
		}
	};
}