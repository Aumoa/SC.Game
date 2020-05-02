#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ��ü�� ���ԵǴ� Ȯ�� ���� ��ҿ� ���� �⺻ �Լ��� �����մϴ�.
	/// </summary>
	public ref class Component abstract : public System::ICloneable
	{
	internal:
		GameObject^ mGameObject;

	protected:
		/// <summary>
		/// <see cref="Component"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Component();

	public:
		/// <summary>
		/// (<see cref="System::ICloneable"/> �������̽����� ���� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�. ���������� ���� ��� <see cref="System::Object::MemberwiseClone"/> �⺻ �Լ��� ���˴ϴ�.
		/// </summary>
		virtual System::Object^ Clone();

		/// <summary>
		/// ����� ��ü�� Ȯ�� ������Ʈ�� �߰��մϴ�.
		/// </summary>
		/// <typeparam name="T"> �߰��� Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ �߰��� �����Ͽ��� ��� �߰��� ������Ʈ��, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component, gcnew()
			T AddComponent();

		/// <summary>
		/// ����� ��ü�� ���Ե� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ������ ��� ������Ʈ ��ü��, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			T GetComponent();

		/// <summary>
		/// ����� ��ü�� ���Ե� Ȯ�� ������Ʈ�� �����մϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ ���ſ� �����Ͽ��� ��� <c>true</c>��, �׷��� ���� ��� <c>false</c>�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			bool RemoveComponent();

		/// <summary>
		/// ���� �켱 Ž�� ��带 ����Ͽ� ����� ��ü�� ������ ���� ������Ʈ���� ���� ó������ �߰��ϴ� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ��� ��ü���� �ϳ� �̻� ������ ��� ������Ʈ ��ü��, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			T GetComponentInChildren();

		/// <summary>
		/// ����� ��ü�� ������ ���� ������Ʈ���� �߰��ϴ� ��� Ȯ�� ������Ʈ�� �����ɴϴ�.
		/// </summary>
		/// <typeparam name="T"> ������ Ȯ�� ������Ʈ Ŭ���� Ÿ���� �����մϴ�. �� Ŭ������ Component Ŭ������ ��� �޾ƾ� �մϴ�. </typeparam>
		/// <returns> ������Ʈ�� ��� ��ü���� �ϳ� �̻� ������ ��� ������Ʈ ��ü �����, �׷��� ���� ��� null�� ��ȯ�մϴ�. </returns>
		generic< class T > where T : Component
			System::Collections::Generic::IList<T>^ GetComponentsInChildren();

		/// <summary>
		/// ����� ��ü�� �����ɴϴ�.
		/// </summary>
		property GameObject^ Object
		{
			Game::GameObject^ get();
		}

		/// <summary>
		/// ����� ��ü�� �ĺ� �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}

		/// <summary>
		/// ����� ��ü�� ��ȯ ��ü�� �����ɴϴ�.
		/// </summary>
		property Game::Transform^ Transform
		{
			Game::Transform^ get();
		}
	};
}