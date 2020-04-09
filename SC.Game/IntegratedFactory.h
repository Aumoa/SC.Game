#pragma once

namespace SC::Game
{
	class IntegratedFactory
	{
	public:
		IntegratedFactory();

		ComPtr<IDXGIAdapter1> SearchHardwareAdapter();

		ComPtr<IDXGIFactory6> pDXGIFactory;
		ComPtr<IDWriteFactory> pDWriteFactory;
		ComPtr<IWICImagingFactory> pWICFactory;
	};
}