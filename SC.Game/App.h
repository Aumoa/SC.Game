#pragma once

#include <Windows.h>
#include <list>
#include <functional>
#include <string>

namespace SC::Game
{
	template< class T >
	using Event = std::list<T>;
	using DisposingDelegate = std::function<void()>;
	using ResizingDelegate = std::function<void( int, int )>;

	class App
	{
	public:
		static HWND hWnd;
		static Event<DisposingDelegate> Disposing;
		static Event<ResizingDelegate> Resizing;
		static int mWidth;
		static int mHeight;

		static std::wstring mAppName;
		static int mPhysicsHz;
		static bool mVSync;
		static bool mDisablePresent;

		static int mFrameIndex;
		static ComPtr<ID3D12Fence> mFence;
		static UINT64 mFenceValue;
		static UINT64 mLastPending[2];
		static HANDLE mFenceEvent;

		static CDeviceContext mHeapCommitDCAndGC;

		static void Initialize();
		static void DisposeAll();
		static void CoreLoop();
		static void GCAdd( ComPtr<IUnknown> pUnknown );

	private:
		static void OnDisposing();
		static void OnIdle();
		static void OnSize( int width, int height );

		static void CreateWindow1();
		static void CreateFence();

		static void Update();
		static void HeapCommit();
		static void Render();

		static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	};
}