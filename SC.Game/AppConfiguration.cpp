using namespace SC;
using namespace SC::Game;

using namespace System;

String^ AppConfiguration::ToString()
{
	return AppName;
}

String^ AppConfiguration::AdapterName::get()
{
	return mAdapterName;
}