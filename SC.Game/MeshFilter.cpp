using namespace SC;
using namespace SC::Game;

using namespace System;

using namespace physx;

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

	if ( mGameObject )
	{
		mGameObject->OnMeshChanged();
	}
}