using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

Mutex GC::mLocker;
vector<GC::tag_Garbage> GC::mGarbages;
size_t GC::mCount;
bool GC::mDisposed;

void GC::Initialize()
{
	App::Disposing.push_front( Dispose );
}

void GC::Add( ID3D12Fence* pFence, UINT64 fenceValue, ComPtr<IUnknown> pUnknown )
{
	auto lock = mLocker.Lock();

	// 가비지 정보를 작성합니다.
	tag_Garbage g;
	g.pUnknown = move( pUnknown );
	g.pFence = move( pFence );
	g.mFenceValue = fenceValue;

	Push( move( g ) );
}

void GC::Collect()
{
	auto lock = mLocker.Lock();

	// 연결 종료된 가비지를 제외한 최고 높이의 큐 크기를 저장합니다.
	size_t maxCount = 0;

	for ( size_t i = 0; i < mCount; ++i )
	{
		// 가비지 정보를 가져옵니다.
		auto& g = mGarbages[i];

		if ( g.pUnknown )
		{
			// 가비지 대상 개체의 사용이 완료되었는지 검사합니다.
			if ( g.pFence->GetCompletedValue() > g.mFenceValue )
			{
				g.pUnknown = nullptr;

				g.pFence = nullptr;
				g.mFenceValue = 0;
			}
			else
			{
				maxCount = i;
			}
		}
	}

	// 큐 크기를 업데이트합니다.
	mCount = maxCount;
}

void GC::Dispose()
{
	mGarbages.clear();
	mDisposed = true;
}

void GC::Push( tag_Garbage&& garbage )
{
	if ( !mDisposed )
	{
		// 용량이 부족할 경우 늘립니다.
		if ( mGarbages.size() <= mCount )
		{
			mGarbages.resize( mGarbages.size() + 512 );
		}

		// 가비지 개체를 추가합니다.
		mGarbages[mCount++] = move( garbage );
	}
}