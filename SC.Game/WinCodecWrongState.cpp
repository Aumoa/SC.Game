using namespace SC;
using namespace SC::Game;

using namespace System;

WinCodecWrongState::WinCodecWrongState( String^ message ) : Exception( message )
{
	HResult = WINCODEC_ERR_WRONGSTATE;
}