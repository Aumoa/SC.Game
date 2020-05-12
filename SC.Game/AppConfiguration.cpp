using namespace SC;
using namespace SC::Game;

using namespace System;

AppConfiguration::AppConfiguration( String^ appName, int physicsUpdatesPerSecond )
{
	AppName = appName;
	PhysicsUpdatesPerSecond = physicsUpdatesPerSecond;
	VSync = false;
}

AppConfiguration::AppConfiguration( String^ appName )
{
	AppName = appName;
	PhysicsUpdatesPerSecond = 60;
	VSync = false;
}

String^ AppConfiguration::ToString()
{
	return String::Format(
		"{0} ({1}Hz)",
		AppName,
		PhysicsUpdatesPerSecond
	);
}

String^ AppConfiguration::AdapterName::get()
{
	return mAdapterName;
}