using namespace SC;
using namespace SC::Game;

using namespace std;

#pragma unmanaged

CDevice::CDevice( IDXGIAdapter1* pAdapter ) : pAdapter( pAdapter )
{
#if defined( _DEBUG )
	// ���� ���α׷��� ����� ���� ����Ǿ��� ���:
	// Direct3D SDK���� ����� ���̾ Ȱ��ȭ�մϴ�.
	if ( ComPtr<ID3D12Debug3> pDebug; SUCCEEDED( D3D12GetDebugInterface( IID_PPV_ARGS( &pDebug ) ) ) )
	{
		//pDebug->SetEnableGPUBasedValidation( TRUE );
		pDebug->EnableDebugLayer();
	}
#endif

	// Direct3D 12 ����̽� ��ü�� �����մϴ�.
	HR( D3D12CreateDevice( pAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS( &pDevice ) ) );
}

void CDevice::InitializeInterop( CCommandQueue* pQueue )
{
	auto pCommandQueue = pQueue->pCommandQueue.Get();

	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D2D1_CREATION_PROPERTIES creationProperties{ };

	creationProperties.threadingMode = D2D1_THREADING_MODE_MULTI_THREADED;
	creationProperties.debugLevel = D2D1_DEBUG_LEVEL_NONE;
	creationProperties.options = D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS;

#if defined( _DEBUG )
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	//creationProperties.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	// D3D11 ȣȯ ��ġ�� �����մϴ�.
	HR( D3D11On12CreateDevice( pDevice.Get(), deviceFlags, nullptr, 0, ( IUnknown** )&pCommandQueue, 1, 0, &pDevice11, &pDeviceContext11, nullptr ) );
	HR( pDevice11.As<ID3D11On12Device>( &pDevice11On12 ) );

	// D3D11 ȣȯ ��ġ���� D2D1 ��ġ�� �����մϴ�.
	ComPtr<IDXGIDevice> pDxgiDevice;
	HR( pDevice11On12.As<IDXGIDevice>( &pDxgiDevice ) );
	HR( D2D1CreateDevice( pDxgiDevice.Get(), creationProperties, &pDevice2D ) );
	HR( pDevice2D->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &pDeviceContext2D ) );
}