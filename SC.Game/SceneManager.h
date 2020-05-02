#pragma once

namespace SC::Game
{
	ref class Scene;

	/// <summary>
	/// ���� �� ��� ����� �����մϴ�.
	/// </summary>
	public ref class SceneManager abstract
	{
	internal:
		static Scene^ mCurrentScene;

	public:
		/// <summary>
		/// ����� �񵿱�� �ҷ��ɴϴ�.
		/// </summary>
		/// <param name="arg"> ����� Load �޼���� ���޵� �Ű� ������ �����մϴ�. </param>
		generic< class T > where T : Scene, gcnew()
			static System::Threading::Tasks::Task<T>^ LoadSceneAsync( System::Object^ arg );

		/// <summary>
		/// ����� �񵿱�� �ҷ��ɴϴ�.
		/// </summary>
		generic< class T > where T : Scene, gcnew()
			static System::Threading::Tasks::Task<T>^ LoadSceneAsync()
		{
			return LoadSceneAsync<T>( nullptr );
		}

		/// <summary>
		/// ����� �ҷ��ɴϴ�.
		/// </summary>
		/// <param name="arg"> ����� Load �޼���� ���޵� �Ű� ������ �����մϴ�. </param>
		generic< class T > where T : Scene, gcnew()
			static T LoadScene( System::Object^ arg );

		/// <summary>
		/// ����� �ҷ��ɴϴ�.
		/// </summary>
		generic< class T > where T : Scene, gcnew()
			static T LoadScene()
		{
			return LoadScene<T>( nullptr );
		}

		/// <summary>
		/// �ش� ����� �����մϴ�.
		/// </summary>
		/// <param name="scene"> ������ ����� �����մϴ�. </param>
		static void Start( Scene^ scene );

	private:
		generic< class T > where T : Scene
			static T MyTask( System::Object^ value );
	};
}