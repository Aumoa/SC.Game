using namespace SC;
using namespace SC::Game::UI;

NavigationEventArgs::NavigationEventArgs( Page^ pageFrom, Page^ pageTo )
{
	mPageFrom = pageFrom;
	mPageTo = pageTo;
}

Page^ NavigationEventArgs::PageFrom::get()
{
	return mPageFrom;
}

Page^ NavigationEventArgs::PageTo::get()
{
	return mPageTo;
}