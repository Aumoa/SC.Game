using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

Bone::Bone() : Component()
{
	mOffset = Matrix4x4::Identity;
	mToRoot = Matrix4x4::Identity;
}

Object^ Bone::Clone()
{
	auto clone = gcnew Bone();
	clone->mName = mName;
	clone->mIndex = mIndex;
	clone->mOffset = mOffset;
	clone->mToRoot = mToRoot;
	return clone;
}

Matrix4x4 Bone::Offset::get()
{
	return mOffset;
}

void Bone::Offset::set( Matrix4x4 value )
{
	mOffset = value;
}

Matrix4x4 Bone::ToRoot::get()
{
	return mToRoot;
}

void Bone::ToRoot::set( Matrix4x4 value )
{
	mToRoot = value;
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