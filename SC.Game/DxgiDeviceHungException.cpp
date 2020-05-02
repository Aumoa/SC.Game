using namespace SC;
using namespace SC::Game;

DxgiDeviceHungException::DxgiDeviceHungException() : Exception( "The GPU will not respond to more commands, most likely because of an invalid command passed by the calling application." )
{
	HResult = DXGI_ERROR_DEVICE_HUNG;
}