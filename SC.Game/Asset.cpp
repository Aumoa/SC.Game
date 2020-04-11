using namespace SC;
using namespace SC::Game;

using namespace System;

Asset::Asset( String^ xName )
{
	mName = xName;
}

String^ Asset::Name::get()
{
	return mName;
}