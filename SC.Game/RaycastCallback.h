#pragma once

namespace SC::Game
{
	class RaycastCallback : public physx::PxRaycastCallback
	{
	public:
		RaycastCallback( physx::PxRaycastHit* hits, int count ) : physx::PxRaycastCallback( hits, count )
		{

		}

		physx::PxAgain processTouches( const physx::PxRaycastHit* buffer, physx::PxU32 nbHits ) override
		{
			return false;
		}
	};
}