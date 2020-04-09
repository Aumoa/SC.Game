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
	// ���� ����� ������ ��� ���� ��鿡 ���� Unload�� �����մϴ�.
	if ( mCurrentScene )
	{
		mCurrentScene->Unload();
	}

	// ���� ���� ��ü�մϴ�.
	mCurrentScene = scene;
}

generic< class T > where T : Scene
T SceneManager::MyTask( Object^ value )
{
	auto t = safe_cast< T >( value );
	t->Load( value );
	return t;
}