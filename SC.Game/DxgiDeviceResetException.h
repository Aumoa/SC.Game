#pragma once

namespace SC::Game
{
	ref class DxgiDeviceResetException : public System::Exception
	{
	public:
		DxgiDeviceResetException();
	};
}