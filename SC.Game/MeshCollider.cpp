using namespace SC;
using namespace SC::Game;

using namespace System;

using namespace physx;

void MeshCollider::Update()
{
	if ( mHasUpdate || Transform->IsUpdated )
	{
		auto scale = Transform->Scale;
		auto meshFilter = GetComponent<MeshFilter^>();

		auto geo = static_cast< PxTriangleMeshGeometry* >( mGeometry );
		if ( meshFilter )
		{
			geo->triangleMesh = meshFilter->Mesh->mTriangleMesh;
			auto scale = Transform->Scale;

			geo->scale.rotation = PxQuat( PxIDENTITY{ } );
			Assign( geo->scale.scale, scale );
		}

		mHasUpdate = true;
	}

	Collider::Update();
}

MeshCollider::MeshCollider() : Collider()
{
	auto meshGeo = new PxTriangleMeshGeometry();

	mGeometry = meshGeo;
}

Object^ MeshCollider::Clone()
{
	auto clone = gcnew MeshCollider();
	CloneAs( clone );
	return clone;
}