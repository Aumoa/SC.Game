using namespace SC;
using namespace SC::Game;

double Time::DeltaTime::get()
{
	return mDeltaTime;
}

void Time::DeltaTime::set( double value )
{
	mDeltaTime = value;
}

double Time::FixedDeltaTime::get()
{
	return mFixedDeltaTime;
}

void Time::FixedDeltaTime::set( double value )
{
	mFixedDeltaTime = value;
}