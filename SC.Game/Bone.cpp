using namespace SC;
using namespace SC::Game;

using namespace System;

Bone::Bone() : Component()
{

}

Object^ Bone::Clone()
{
	auto clone = gcnew Bone();
	clone->mName = mName;
	clone->mIndex = mIndex;
	return clone;
}

String^ Bone::Name::get()
{
	return mName;
}

void Bone::Name::set( String^ value )
{
	mName = value;
}

int Bone::Index::get()
{
	return mIndex;
}

void Bone::Index::set( int value )
{
	mIndex = value;
}