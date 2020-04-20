using namespace SC;
using namespace SC::Game;

void StateMachine::Interpolate( float timeDelta )
{
	if ( Clip != nullptr )
	{
		TimePos += timeDelta;
		Clip->Interpolate( TimePos, Keyframes );
	}
}