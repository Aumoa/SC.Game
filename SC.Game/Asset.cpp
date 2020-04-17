using namespace SC;
using namespace SC::Game;

using namespace System;

Asset::Asset( String^ xName )
{
	mName = xName;
}

String^ Asset::ToString()
{
	return String::Format(
		"{0}:{1}", Object::ToString(), mName
	);
}

String^ Asset::Name::get()
{
	return mName;
}