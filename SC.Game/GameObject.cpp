using namespace SC;
using namespace SC::Game;

using namespace System;

GameObject::GameObject( String^ xName )
{
	mName = xName;
}

String^ GameObject::Name::get()
{
	return mName;
}