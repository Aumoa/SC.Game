#pragma once

namespace SC::Game
{
	class AlignedHeap
	{
		static constexpr const UINT64 mAllocUnit = 256;

	public:
		ComPtr<ID3D12Resource> pResource;
		ComPtr<ID3D12Resource> pUploadHeaps[2];

		D3D12_GPU_VIRTUAL_ADDRESS mStartAddress;
		UINT64 mAlign;
		UINT64 mCount;
		std::queue<UINT64> mQueue;
		Mutex mLocker;

		std::map<UINT64, UINT64> mCopyRangeQueue[2];

		void* pUploadAddress[2];

		ComPtr<ID3D12Resource> pExpandCopy;

	public:
		AlignedHeap( UINT64 alignment );
		AlignedHeap( AlignedHeap&& mov );

		UINT64 Alloc();
		void Free( UINT64 index );
		void Commit( int frameIndex, CDeviceContext& deviceContext );
		bool IsCommittable( int frameIndex );

		D3D12_GPU_VIRTUAL_ADDRESS GetVirtualAddress( UINT64 index );
		void* GetUploadAddress( int frameIndex, UINT64 index );
		void AddCopyRange( int frameIndex, const D3D12_RANGE& range );

	private:
		UINT64 Expand();
	};

	class HeapAllocator abstract
	{
		static std::vector<AlignedHeap> mAlignedHeaps;
		static std::set<LargeHeap*> mLargeHeaps;

	public:
		static bool mHeapValid;

	public:
		static void Initialize();
		static void Commit( int frameIndex, CDeviceContext& deviceContext );
		static ComPtr<Heap> Alloc( UINT64 sizeInBytes );
		static void LinkLargeHeap( LargeHeap* pLargeHeap );
		static void UnlinkLargeHeap( LargeHeap* pLargeHeap );

	private:
		static void Dispose();
	};
}