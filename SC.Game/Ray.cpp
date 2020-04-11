using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

Ray::Ray( Vector3 origin, Vector3 direction )
{
	this->Origin = origin;
	this->Direction = direction;
	this->MaxDepth = 0.0f;
}

Ray::Ray( Vector3 origin, Vector3 direction, float maxDepth )
{
	this->Origin = origin;
	this->Direction = direction;
	this->MaxDepth = maxDepth;
}

String^ Ray::ToString()
{
	return String::Format( "{0}->{1}", Origin, Direction );
}

Vector3 Ray::GetPoint( float distance )
{
	return Origin + Direction * distance;
}