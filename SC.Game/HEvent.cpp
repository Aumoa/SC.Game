using namespace SC;
using namespace SC::Game;

#pragma unmanaged

HEvent::HEvent()
{
	mHandle = CreateEventExW( nullptr, nullptr, 0, GENERIC_ALL );
}

HEvent::HEvent( HEvent&& mov )
{
	mHandle = mov.mHandle;
	mov.mHandle = nullptr;
}

HEvent::~HEvent()
{
	if ( mHandle )
	{
		CloseHandle( mHandle );
		mHandle = nullptr;
	}
}

void HEvent::WaitForSingleObject()
{
	::WaitForSingleObject( mHandle, INFINITE );
}

HEvent& HEvent::operator=( HEvent&& mov )
{
	mHandle = mov.mHandle;
	mov.mHandle = nullptr;

	return *this;
}