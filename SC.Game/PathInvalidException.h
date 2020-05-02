#pragma once

namespace SC::Game
{
	ref class PathInvalidException : public System::Exception
	{
	public:
		PathInvalidException();
	};
}