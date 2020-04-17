using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;

Component::Component()
{

}

Object^ Component::Clone()
{
	return MemberwiseClone();
}

generic< class T > where T : Component, gcnew()
T Component::AddComponent()
{
	return mGameObject->AddComponent<T>();
}

generic< class T > where T : Component
T Component::GetComponent()
{
	return mGameObject->GetComponent<T>();
}

generic< class T > where T : Component
bool Component::RemoveComponent()
{
	return mGameObject->RemoveComponent<T>();
}

generic< class T > where T : Component
T Component::GetComponentInChildren()
{
	return mGameObject->GetComponentInChildren<T>();
}

generic< class T > where T : Component
IList<T>^ Component::GetComponentsInChildren()
{
	return mGameObject->GetComponentsInChildren<T>();
}

GameObject^ Component::Object::get()
{
	return mGameObject;
}

String^ Component::Name::get()
{
	return mGameObject->Name;
}

Transform^ Component::Transform::get()
{
	return mGameObject->Transform;
}