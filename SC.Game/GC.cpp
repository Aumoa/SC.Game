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

	// ������ ������ �ۼ��մϴ�.
	tag_Garbage g;
	g.pUnknown = move( pUnknown );
	g.pFence = move( pFence );
	g.mFenceValue = fenceValue;

	Push( move( g ) );
}

void GC::Collect()
{
	auto lock = mLocker.Lock();

	// ���� ����� �������� ������ �ְ� ������ ť ũ�⸦ �����մϴ�.
	size_t maxCount = 0;

	for ( size_t i = 0; i < mCount; ++i )
	{
		// ������ ������ �����ɴϴ�.
		auto& g = mGarbages[i];

		if ( g.pUnknown )
		{
			// ������ ��� ��ü�� ����� �Ϸ�Ǿ����� �˻��մϴ�.
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

	// ť ũ�⸦ ������Ʈ�մϴ�.
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
		// �뷮�� ������ ��� �ø��ϴ�.
		if ( mGarbages.size() <= mCount )
		{
			mGarbages.resize( mGarbages.size() + 512 );
		}

		// ������ ��ü�� �߰��մϴ�.
		mGarbages[mCount++] = move( garbage );
	}
}