#pragma once

namespace SC
{
	class Mutex;

	class UniqueLock
	{
		Mutex* mMutex = nullptr;

	public:
		UniqueLock( Mutex* pMutex );
		UniqueLock( UniqueLock&& right );
		UniqueLock( const UniqueLock& ) = delete;
		~UniqueLock();

		Mutex* Detach();
	};

	class Mutex
	{
		CRITICAL_SECTION mCriticalSection;

	public:
		Mutex();
		~Mutex();

		UniqueLock Lock();
		bool TryLock();
		void Unlock();
	};
}