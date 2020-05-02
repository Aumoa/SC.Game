#pragma once

namespace SC::Game
{
	ref class DxgiDeviceHungException : public System::Exception
	{
	public:
		DxgiDeviceHungException();
	};
}