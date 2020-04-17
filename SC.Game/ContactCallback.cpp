using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;

using namespace physx;

void ContactCallback::onConstraintBreak( PxConstraintInfo* constraints, PxU32 count )
{

}

void ContactCallback::onWake( PxActor** actors, PxU32 count )
{

}

void ContactCallback::onSleep( PxActor** actors, PxU32 count )
{

}

void ContactCallback::onContact( const PxContactPairHeader& pairHeader, const PxContactPair* contactPairs, PxU32 contactCount )
{
	auto& gameObject0 = *( gcroot<GameObject^>* )pairHeader.actors[0]->userData;
	auto& gameObject1 = *( gcroot<GameObject^>* )pairHeader.actors[1]->userData;

	//List<ContactPoint>^ contacts = gcnew List<ContactPoint>( contactCount );

	auto& pair = contactPairs[0];

	if ( pair.flags & PxContactPairFlag::eACTOR_PAIR_HAS_FIRST_TOUCH )
	{
		Collision collision;
		collision.Object = gameObject0;
		collision.Target = gameObject1;
		gameObject0->OnCollisionEnter( collision );

		collision.Object = gameObject1;
		collision.Target = gameObject0;
		gameObject1->OnCollisionEnter( collision );
	}
}

void ContactCallback::onTrigger( PxTriggerPair* pairs, PxU32 count )
{
	for ( int i = 0, c = ( int )count; i < c; ++i )
	{
		auto& pair = pairs[i];

		auto gameObject0 = *( gcroot<GameObject^>* )pair.triggerActor->userData;
		auto gameObject1 = *( gcroot<GameObject^>* )pair.otherActor->userData;

		if ( pair.status & PxPairFlag::eNOTIFY_TOUCH_FOUND )
		{
			if ( gameObject0 ) gameObject0->OnTriggerEnter( *( gcroot<Collider^>* )pair.otherShape->userData );
			if ( gameObject1 ) gameObject1->OnTriggerEnter( *( gcroot<Collider^>* )pair.triggerShape->userData );
		}
		else if ( pair.status & PxPairFlag::eNOTIFY_TOUCH_LOST )
		{
			if ( gameObject0 ) gameObject0->OnTriggerExit( *( gcroot<Collider^>* )pair.otherShape->userData );
			if ( gameObject1 ) gameObject1->OnTriggerExit( *( gcroot<Collider^>* )pair.triggerShape->userData );
		}
	}
}

void ContactCallback::onAdvance( const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count )
{

}