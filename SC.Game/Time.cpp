using namespace SC;
using namespace SC::Game;

float Time::DeltaTime::get()
{
	return mDeltaTime;
}

void Time::DeltaTime::set( float value )
{
	mDeltaTime = value;
}

float Time::FixedDeltaTime::get()
{
	return mFixedDeltaTime;
}

void Time::FixedDeltaTime::set( float value )
{
	mFixedDeltaTime = value;
}