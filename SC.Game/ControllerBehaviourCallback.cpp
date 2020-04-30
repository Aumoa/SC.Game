using namespace SC;
using namespace SC::Game;

using namespace physx;

PxControllerBehaviorFlags ControllerBehaviourCallback::getBehaviorFlags( const PxShape& shape, const PxActor& actor )
{
	return PxControllerBehaviorFlag::eCCT_SLIDE;
}

PxControllerBehaviorFlags ControllerBehaviourCallback::getBehaviorFlags( const PxController& controller )
{
	return PxControllerBehaviorFlag::eCCT_SLIDE;
}

PxControllerBehaviorFlags ControllerBehaviourCallback::getBehaviorFlags( const PxObstacle& obstacle )
{
	return PxControllerBehaviorFlag::eCCT_SLIDE;
}