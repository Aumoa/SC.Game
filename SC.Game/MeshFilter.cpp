using namespace SC;
using namespace SC::Game;

using namespace System;

MeshFilter::MeshFilter()
{

}

Object^ MeshFilter::Clone()
{
	auto clone = gcnew MeshFilter();
	clone->mMesh = mMesh;
	return clone;
}

Mesh^ MeshFilter::Mesh::get()
{
	return mMesh;
}

void MeshFilter::Mesh::set( Game::Mesh^ value )
{
	mMesh = value;
}