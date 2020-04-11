using namespace SC;
using namespace SC::Game;

void Behaviour::InternalUpdate()
{
	if ( mIsFirst )
	{
		Start();
		mIsFirst = false;
	}

	Update();
}

Behaviour::Behaviour() : Component()
{

}

void Behaviour::Awake()
{

}

void Behaviour::Start()
{

}

void Behaviour::Update()
{

}

void Behaviour::FixedUpdate()
{

}

void Behaviour::LateUpdate()
{

}