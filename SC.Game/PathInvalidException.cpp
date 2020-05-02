using namespace SC;
using namespace SC::Game;

PathInvalidException::PathInvalidException() : Exception( "The filename, directory name or volume label syntax is incorrect." )
{
	HResult = 0x8007007B;
}