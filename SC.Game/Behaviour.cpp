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

void Behaviour::OnCollisionEnter( Collision collision )
{

}

void Behaviour::OnCollisionExit( Collision collision )
{

}

void Behaviour::OnCollisionStay( Collision collision )
{

}

void Behaviour::OnTriggerEnter( Collider^ collider )
{

}

void Behaviour::OnTriggerExit( Collider^ collider )
{

}