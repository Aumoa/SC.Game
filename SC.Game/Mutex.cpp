using namespace SC;

#pragma unmanaged

Mutex::Mutex()
{
	InitializeCriticalSection( &mCriticalSection );
}

Mutex::~Mutex()
{
	DeleteCriticalSection( &mCriticalSection );
}

UniqueLock Mutex::Lock()
{
	EnterCriticalSection( &mCriticalSection );
	return this;
}

bool Mutex::TryLock()
{
	return ( bool )TryEnterCriticalSection( &mCriticalSection );
}

void Mutex::Unlock()
{
	LeaveCriticalSection( &mCriticalSection );
}

UniqueLock::UniqueLock( Mutex* pMutex )
{
	mMutex = pMutex;
}

UniqueLock::UniqueLock( UniqueLock&& right )
{
	mMutex = right.Detach();
}

UniqueLock::~UniqueLock()
{
	if ( mMutex )
	{
		mMutex->Unlock();
		mMutex = nullptr;
	}
}

Mutex* UniqueLock::Detach()
{
	auto ret = mMutex;
	mMutex = nullptr;
	return ret;
}