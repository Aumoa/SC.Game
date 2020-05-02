using namespace SC;
using namespace SC::Game;

DxgiDeviceResetException::DxgiDeviceResetException() : Exception( "The GPU will not respond to more commands, most likely because some other application submitted invalid commands. The calling application should re-create the device and continue." )
{
	HResult = DXGI_ERROR_DEVICE_RESET;
}