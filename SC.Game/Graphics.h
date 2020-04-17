#pragma once

namespace SC::Game
{
	class Graphics
	{
	public:
		static std::unique_ptr<IntegratedFactory> mFactory;
		static std::unique_ptr<CDevice> mDevice;
		static std::unique_ptr<CCommandQueue> mCoreQueue;
		static std::unique_ptr<CCommandQueue> mHighPriorityQueue;
		static std::unique_ptr<CCommandQueue> mUIQueue;
		static std::unique_ptr<CCommandQueue> mCopyQueue;
		static std::unique_ptr<CCommandQueue> mComputeQueue;
		static std::unique_ptr<CSwapChain> mSwapChain;

	public:
		static void Initialize();

	private:
		static void OnDisposing();
		static void OnResizing( int width, int height );
	};
}