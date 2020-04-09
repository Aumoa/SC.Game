#pragma once

namespace SC::Game
{
	class CCommandQueue;

	class CDevice
	{
	public:
		CDevice( IDXGIAdapter1* pAdapter );

		void InitializeInterop( CCommandQueue* pQueue );

	public:
		ComPtr<IDXGIAdapter1> pAdapter;
		ComPtr<ID3D12Device5> pDevice;
		ComPtr<ID3D11Device> pDevice11;
		ComPtr<ID3D11On12Device> pDevice11On12;
		ComPtr<ID3D11DeviceContext> pDeviceContext11;
		ComPtr<ID2D1Device> pDevice2D;
		ComPtr<ID2D1DeviceContext> pDeviceContext2D;
	};
}