#pragma once

namespace SC::Game
{
	class ControllerBehaviourCallback : public physx::PxControllerBehaviorCallback
	{
		physx::PxControllerBehaviorFlags getBehaviorFlags( const physx::PxShape& shape, const physx::PxActor& actor ) override;
		physx::PxControllerBehaviorFlags getBehaviorFlags( const physx::PxController& controller ) override;
		physx::PxControllerBehaviorFlags getBehaviorFlags( const physx::PxObstacle& obstacle ) override;
	};
}