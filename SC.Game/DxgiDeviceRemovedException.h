#pragma once

namespace SC::Game
{
	ref class DxgiDeviceRemovedException : public System::Exception
	{
	public:
		DxgiDeviceRemovedException();
	};
}