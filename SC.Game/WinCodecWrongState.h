#pragma once

namespace SC::Game
{
	ref class WinCodecWrongState : public System::Exception
	{
	public:
		WinCodecWrongState( System::String^ message );
	};
}