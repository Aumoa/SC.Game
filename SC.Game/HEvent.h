#pragma once

namespace SC::Game
{
	class HEvent
	{
	public:
		HANDLE mHandle = nullptr;

	public:
		HEvent();
		HEvent( HEvent&& mov );
		~HEvent();

		void WaitForSingleObject();

		HEvent& operator=( HEvent&& mov );
	};
}