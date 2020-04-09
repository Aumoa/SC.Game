using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Threading;
using namespace System::Threading::Tasks;

generic< class T > where T : Scene, gcnew()
Task<T>^ SceneManager::LoadSceneAsync( Object^ arg )
{
	return Task<T>::Factory->StartNew( gcnew System::Func<Object^, T>( MyTask<T> ), gcnew T() );
}

generic< class T > where T : Scene, gcnew()
T SceneManager::LoadScene( Object^ arg )
{
	auto scene = gcnew T();
	scene->Load( arg );
	return scene;
}

void SceneManager::Start( Scene^ scene )
{
	// 기존 장면이 존재할 경우 기존 장면에 대해 Unload를 수행합니다.
	if ( mCurrentScene )
	{
		mCurrentScene->Unload();
	}

	// 기존 장면과 교체합니다.
	mCurrentScene = scene;
}

generic< class T > where T : Scene
T SceneManager::MyTask( Object^ value )
{
	auto t = safe_cast< T >( value );
	t->Load( value );
	return t;
}