using namespace SC;
using namespace SC::Game;

DxgiDeviceRemovedException::DxgiDeviceRemovedException() : Exception( "The GPU device instance has been suspended. Use GetDeviceRemovedReason to determine the appropriate action." )
{
	HResult = DXGI_ERROR_DEVICE_REMOVED;
}