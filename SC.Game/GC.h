#pragma once

namespace SC::Game
{
	class GC abstract
	{
		struct tag_Garbage
		{
			ComPtr<IUnknown> pUnknown;
			ID3D12Fence* pFence;
			UINT64 mFenceValue;
		};

		static Mutex mLocker;
		static std::vector<tag_Garbage> mGarbages;
		static std::size_t mCount;
		static bool mDisposed;

	public:
		static void Initialize();
		static void Add( ID3D12Fence* pFence, UINT64 fenceValue, ComPtr<IUnknown> pUnknown );
		static void Collect();

	private:
		static void Dispose();
		static void Push( tag_Garbage&& garbage );
	};
}