using namespace SC;
using namespace SC::Game;

ThreadDispatcher::ThreadDispatcher()
{

}

int ThreadDispatcher::ID::get()
{
	return mID;
}

void ThreadDispatcher::ID::set( int value )
{
	mID = value;
}