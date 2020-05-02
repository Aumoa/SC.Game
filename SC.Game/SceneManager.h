#pragma once

namespace SC::Game
{
	ref class Scene;

	/// <summary>
	/// 게임 내 모든 장면을 관리합니다.
	/// </summary>
	public ref class SceneManager abstract
	{
	internal:
		static Scene^ mCurrentScene;

	public:
		/// <summary>
		/// 장면을 비동기로 불러옵니다.
		/// </summary>
		/// <param name="arg"> 장면의 Load 메서드로 전달될 매개 변수를 전달합니다. </param>
		generic< class T > where T : Scene, gcnew()
			static System::Threading::Tasks::Task<T>^ LoadSceneAsync( System::Object^ arg );

		/// <summary>
		/// 장면을 비동기로 불러옵니다.
		/// </summary>
		generic< class T > where T : Scene, gcnew()
			static System::Threading::Tasks::Task<T>^ LoadSceneAsync()
		{
			return LoadSceneAsync<T>( nullptr );
		}

		/// <summary>
		/// 장면을 불러옵니다.
		/// </summary>
		/// <param name="arg"> 장면의 Load 메서드로 전달될 매개 변수를 전달합니다. </param>
		generic< class T > where T : Scene, gcnew()
			static T LoadScene( System::Object^ arg );

		/// <summary>
		/// 장면을 불러옵니다.
		/// </summary>
		generic< class T > where T : Scene, gcnew()
			static T LoadScene()
		{
			return LoadScene<T>( nullptr );
		}

		/// <summary>
		/// 해당 장면을 시작합니다.
		/// </summary>
		/// <param name="scene"> 시작할 장면을 전달합니다. </param>
		static void Start( Scene^ scene );

	private:
		generic< class T > where T : Scene
			static T MyTask( System::Object^ value );
	};
}