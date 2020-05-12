using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Collections::Generic;

using namespace std;
using namespace physx;

void Mesh::Initialize( const void* pVertexBuffer, unsigned int vertexStride, const unsigned int* pIndexBuffer, unsigned int vertexCount, unsigned int indexCount )
{
	SIZE_T sizeInBytes = vertexStride * vertexCount;

	mVertexBuffer = new ImmutableHeap( sizeInBytes, pVertexBuffer );
	mIndexBuffer = new ImmutableHeap( sizeof( UINT ) * indexCount, pIndexBuffer );

	mVertexCount = vertexCount;
	mIndexCount = indexCount;

	PxConvexMeshDesc convexMeshDesc;
	convexMeshDesc.setToDefault();
	convexMeshDesc.points.count = vertexCount;
	convexMeshDesc.points.data = pVertexBuffer;
	convexMeshDesc.points.stride = vertexStride;
	convexMeshDesc.indices.count = indexCount;
	convexMeshDesc.indices.data = pIndexBuffer;
	convexMeshDesc.indices.stride = sizeof( UINT );
	convexMeshDesc.flags = PxConvexFlag::eFAST_INERTIA_COMPUTATION | PxConvexFlag::eDISABLE_MESH_VALIDATION | PxConvexFlag::eCOMPUTE_CONVEX;

	PxTriangleMeshDesc triangleMeshDesc;
	triangleMeshDesc.setToDefault();
	triangleMeshDesc.points.count = vertexCount;
	triangleMeshDesc.points.data = pVertexBuffer;
	triangleMeshDesc.points.stride = vertexStride;
	triangleMeshDesc.triangles.count = indexCount / 3;
	triangleMeshDesc.triangles.data = pIndexBuffer;
	triangleMeshDesc.triangles.stride = sizeof( UINT ) * 3;

	PxDefaultMemoryOutputStream buffer;
	if ( Physics::mCooking->cookConvexMesh( convexMeshDesc, buffer ) )
	{
		mConvexMesh = Physics::mCooking->createConvexMesh( convexMeshDesc, Physics::mPhysics->getPhysicsInsertionCallback() );
		mTriangleMesh = Physics::mCooking->createTriangleMesh( triangleMeshDesc, Physics::mPhysics->getPhysicsInsertionCallback() );
	}
}

Mesh::Mesh( String^ xName ) : Asset( xName )
{

}

void Mesh::Initialize( const vector<tag_Vertex>& vertexBuffer, const vector<unsigned int>& indexBuffer )
{
	Initialize( vertexBuffer.data(), sizeof( tag_Vertex ), indexBuffer.data(), ( UINT )vertexBuffer.size(), ( UINT )indexBuffer.size() );
}

void Mesh::Initialize( const vector<tag_SkinnedVertex>& vertexBuffer, const vector<unsigned int>& indexBuffer )
{
	mIsSkinned = true;

	Initialize( vertexBuffer.data(), sizeof( tag_SkinnedVertex ), indexBuffer.data(), ( UINT )vertexBuffer.size(), ( UINT )indexBuffer.size() );
}

void Mesh::DrawIndexed( CDeviceContext& deviceContext )
{
	D3D12_VERTEX_BUFFER_VIEW vbv{ };
	vbv.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
	vbv.SizeInBytes = ( mIsSkinned ? sizeof( tag_SkinnedVertex ) : sizeof( tag_Vertex ) ) * mVertexCount;
	vbv.StrideInBytes = ( mIsSkinned ? sizeof( tag_SkinnedVertex ) : sizeof( tag_Vertex ) );

	deviceContext.IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	deviceContext.IASetVertexBuffers( 0, 1, &vbv );

	if ( mIndexBuffer )
	{
		D3D12_INDEX_BUFFER_VIEW ibv{ };
		ibv.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
		ibv.SizeInBytes = sizeof( UINT ) * mIndexCount;
		ibv.Format = DXGI_FORMAT_R32_UINT;

		deviceContext.IASetIndexBuffer( &ibv );
		deviceContext.DrawIndexedInstanced( ( UINT )mIndexCount, 1, 0, 0, 0 );
	}
	else
	{
		deviceContext.DrawInstanced( ( UINT )mVertexCount, 1, 0, 0 );
	}
}

void Mesh::DrawSkinnedIndexed( UINT64 virtualAddress, CDeviceContext& deviceContext )
{
	D3D12_VERTEX_BUFFER_VIEW vbv{ };
	vbv.BufferLocation = virtualAddress;
	vbv.SizeInBytes = sizeof( tag_Vertex ) * mVertexCount;
	vbv.StrideInBytes = sizeof( tag_Vertex );

	deviceContext.IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	deviceContext.IASetVertexBuffers( 0, 1, &vbv );

	if ( mIndexBuffer )
	{
		D3D12_INDEX_BUFFER_VIEW ibv{ };
		ibv.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
		ibv.SizeInBytes = sizeof( UINT ) * mIndexCount;
		ibv.Format = DXGI_FORMAT_R32_UINT;

		deviceContext.IASetIndexBuffer( &ibv );
		deviceContext.DrawIndexedInstanced( ( UINT )mIndexCount, 1, 0, 0, 0 );
	}
	else
	{
		deviceContext.DrawInstanced( ( UINT )mVertexCount, 1, 0, 0 );
	}
}

Mesh::~Mesh()
{
	this->!Mesh();
}

Mesh::!Mesh()
{
	if ( mVertexBuffer )
	{
		ComPtr<IUnknown> pUnknown;
		pUnknown.Attach( mVertexBuffer );
		App::GCAdd( move( pUnknown ) );
		mVertexBuffer = nullptr;
	}

	if ( mIndexBuffer )
	{
		ComPtr<IUnknown> pUnknown;
		pUnknown.Attach( mIndexBuffer );
		App::GCAdd( move( pUnknown ) );
		mIndexBuffer = nullptr;
	}

	if ( !App::mDisposed )
	{
		if ( mConvexMesh )
		{
			mConvexMesh->release();
			mConvexMesh = nullptr;
		}
	}
}

bool Mesh::IsSkinned::get()
{
	return mIsSkinned;
}

Mesh^ Mesh::CreateMesh( String^ xName, IList<Vertex>^ vertexBuffer, IList<UInt32>^ indexBuffer )
{
	vector<tag_Vertex> raw_vertexBuffer( vertexBuffer->Count );
	vector<UINT> raw_indexBuffer( indexBuffer->Count );

	for ( int i = 0; i < vertexBuffer->Count; ++i )
	{
		auto v1 = vertexBuffer[i];
		auto& v2 = raw_vertexBuffer[i];

		v2.Pos = { v1.Pos.X, v1.Pos.Y, v1.Pos.Z };
		v2.Color = { v1.Color.X, v1.Color.Y, v1.Color.Z, v1.Color.W };
		v2.Tex = { v1.Tex.X, v1.Tex.Y };
		v2.Normal = { v1.Normal.X, v1.Normal.Y, v1.Normal.Z };
		v2.Tangent = { v1.Tangent.X, v1.Tangent.Y, v1.Tangent.Z };
	}

	for ( int i = 0; i < indexBuffer->Count; ++i )
	{
		raw_indexBuffer[i] = indexBuffer[i];
	}

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( raw_vertexBuffer, raw_indexBuffer );

	return mesh;
}

Mesh^ Mesh::CreateMesh( String^ xName, IList<SkinnedVertex>^ vertexBuffer, IList<UInt32>^ indexBuffer )
{
	vector<tag_SkinnedVertex> raw_vertexBuffer( vertexBuffer->Count );
	vector<UINT> raw_indexBuffer( indexBuffer->Count );

	for ( int i = 0; i < vertexBuffer->Count; ++i )
	{
		auto v1 = vertexBuffer[i];
		auto& v2 = raw_vertexBuffer[i];

		v2.Pos = { v1.Pos.X, v1.Pos.Y, v1.Pos.Z };
		v2.Color = { v1.Color.X, v1.Color.Y, v1.Color.Z, v1.Color.W };
		v2.Tex = { v1.Tex.X, v1.Tex.Y };
		v2.Normal = { v1.Normal.X, v1.Normal.Y, v1.Normal.Z };
		v2.Tangent = { v1.Tangent.X, v1.Tangent.Y, v1.Tangent.Z };
		v2.Weights[0] = v1.Weights.X;
		v2.Weights[1] = v1.Weights.Y;
		v2.Weights[2] = v1.Weights.Z;
		v2.Indices[0] = v1.Indices.X;
		v2.Indices[1] = v1.Indices.Y;
		v2.Indices[2] = v1.Indices.Z;
		v2.Indices[3] = v1.Indices.W;
	}

	for ( int i = 0; i < indexBuffer->Count; ++i )
	{
		raw_indexBuffer[i] = indexBuffer[i];
	}

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( raw_vertexBuffer, raw_indexBuffer );

	return mesh;
}

Mesh^ Mesh::CreatePlane( String^ xName, float texScaleX, float texScaleY, int gridCountX, int gridCountY )
{
	int vertexCountX = gridCountX + 1;
	int vertexCountY = gridCountY + 1;

	vector<tag_Vertex> vertexBuffer( vertexCountX * vertexCountY );
	vector<UINT> indexBuffer( gridCountX * gridCountY * 6 );

	float xPosBeg = -1.0f;
	float yPosBeg = 1.0f;
	float xPosStride = 2.0f / gridCountX;
	float yPosStride = -2.0f / gridCountY;
	float xTexStride = texScaleX / gridCountX;
	float yTexStride = texScaleY / gridCountY;

	for ( int j = 0; j < vertexCountY; ++j )
	{
		for ( int i = 0; i < vertexCountX; ++i )
		{
			tag_Vertex v;

			v.Pos = { xPosBeg + xPosStride * i, 0.0f, yPosBeg + yPosStride * j };
			v.Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			v.Tex = { xTexStride * i, yTexStride * j };
			v.Normal = { 0.0f, 1.0f, 0.0f };
			v.Tangent = { 1.0f, 0.0f, 0.0f };

			vertexBuffer[j * vertexCountX + i] = v;
		}
	}

	for ( int j = 0; j < gridCountY; ++j )
	{
		for ( int i = 0; i < gridCountX; ++i )
		{
			int base = j * vertexCountX + i;
			auto arr = ( int( & )[6] )indexBuffer[( j * gridCountX + i ) * 6];
			arr[0] = base;
			arr[1] = base + 1;
			arr[2] = base + vertexCountX;
			arr[3] = base + 1;
			arr[4] = base + vertexCountX + 1;
			arr[5] = base + vertexCountX;
		}
	}

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );

	return mesh;
}

Mesh^ Mesh::CreateCube( String^ xName )
{
	vector<tag_Vertex> vertexBuffer( 24 );
	vector<UINT> indexBuffer( 36 );

	/* Front */
	vertexBuffer[0].Pos = { -1.0f, +1.0f, -1.0f };
	vertexBuffer[1].Pos = { +1.0f, +1.0f, -1.0f };
	vertexBuffer[2].Pos = { +1.0f, -1.0f, -1.0f };
	vertexBuffer[3].Pos = { -1.0f, -1.0f, -1.0f };

	vertexBuffer[0].Normal = { +0.0f, +0.0f, -1.0f };
	vertexBuffer[1].Normal = { +0.0f, +0.0f, -1.0f };
	vertexBuffer[2].Normal = { +0.0f, +0.0f, -1.0f };
	vertexBuffer[3].Normal = { +0.0f, +0.0f, -1.0f };

	vertexBuffer[0].Tangent = { +1.0f, +0.0f, +0.0f };
	vertexBuffer[1].Tangent = { +1.0f, +0.0f, +0.0f };
	vertexBuffer[2].Tangent = { +1.0f, +0.0f, +0.0f };
	vertexBuffer[3].Tangent = { +1.0f, +0.0f, +0.0f };

	/* Back */
	vertexBuffer[4].Pos = { +1.0f, +1.0f, +1.0f };
	vertexBuffer[5].Pos = { -1.0f, +1.0f, +1.0f };
	vertexBuffer[6].Pos = { -1.0f, -1.0f, +1.0f };
	vertexBuffer[7].Pos = { +1.0f, -1.0f, +1.0f };

	vertexBuffer[4].Normal = { +0.0f, +0.0f, +1.0f };
	vertexBuffer[5].Normal = { +0.0f, +0.0f, +1.0f };
	vertexBuffer[6].Normal = { +0.0f, +0.0f, +1.0f };
	vertexBuffer[7].Normal = { +0.0f, +0.0f, +1.0f };

	vertexBuffer[4].Tangent = { -1.0f, +0.0f, +0.0f };
	vertexBuffer[5].Tangent = { -1.0f, +0.0f, +0.0f };
	vertexBuffer[6].Tangent = { -1.0f, +0.0f, +0.0f };
	vertexBuffer[7].Tangent = { -1.0f, +0.0f, +0.0f };

	/* Right */
	vertexBuffer[8].Pos = { +1.0f, +1.0f, -1.0f };
	vertexBuffer[9].Pos = { +1.0f, +1.0f, +1.0f };
	vertexBuffer[10].Pos = { +1.0f, -1.0f, +1.0f };
	vertexBuffer[11].Pos = { +1.0f, -1.0f, -1.0f };

	vertexBuffer[8].Normal = { +1.0f, +0.0f, +0.0f };
	vertexBuffer[9].Normal = { +1.0f, +0.0f, +0.0f };
	vertexBuffer[10].Normal = { +1.0f, +0.0f, +0.0f };
	vertexBuffer[11].Normal = { +1.0f, +0.0f, +0.0f };

	vertexBuffer[8].Tangent = { -0.0f, +0.0f, +1.0f };
	vertexBuffer[9].Tangent = { -0.0f, +0.0f, +1.0f };
	vertexBuffer[10].Tangent = { -0.0f, +0.0f, +1.0f };
	vertexBuffer[11].Tangent = { -0.0f, +0.0f, +1.0f };

	/* Left */
	vertexBuffer[12].Pos = { -1.0f, +1.0f, +1.0f };
	vertexBuffer[13].Pos = { -1.0f, +1.0f, -1.0f };
	vertexBuffer[14].Pos = { -1.0f, -1.0f, -1.0f };
	vertexBuffer[15].Pos = { -1.0f, -1.0f, +1.0f };

	vertexBuffer[12].Normal = { -1.0f, +0.0f, +0.0f };
	vertexBuffer[13].Normal = { -1.0f, +0.0f, +0.0f };
	vertexBuffer[14].Normal = { -1.0f, +0.0f, +0.0f };
	vertexBuffer[15].Normal = { -1.0f, +0.0f, +0.0f };

	vertexBuffer[12].Tangent = { -0.0f, +0.0f, -1.0f };
	vertexBuffer[13].Tangent = { -0.0f, +0.0f, -1.0f };
	vertexBuffer[14].Tangent = { -0.0f, +0.0f, -1.0f };
	vertexBuffer[15].Tangent = { -0.0f, +0.0f, -1.0f };

	/* Top */
	vertexBuffer[16].Pos = { -1.0f, +1.0f, +1.0f };
	vertexBuffer[17].Pos = { +1.0f, +1.0f, +1.0f };
	vertexBuffer[18].Pos = { +1.0f, +1.0f, -1.0f };
	vertexBuffer[19].Pos = { -1.0f, +1.0f, -1.0f };

	vertexBuffer[16].Normal = { -0.0f, +1.0f, +0.0f };
	vertexBuffer[17].Normal = { -0.0f, +1.0f, +0.0f };
	vertexBuffer[18].Normal = { -0.0f, +1.0f, +0.0f };
	vertexBuffer[19].Normal = { -0.0f, +1.0f, +0.0f };

	vertexBuffer[16].Tangent = { +1.0f, +0.0f, -1.0f };
	vertexBuffer[17].Tangent = { +1.0f, +0.0f, -1.0f };
	vertexBuffer[18].Tangent = { +1.0f, +0.0f, -1.0f };
	vertexBuffer[19].Tangent = { +1.0f, +0.0f, -1.0f };

	/* Bottom */
	vertexBuffer[20].Pos = { +1.0f, -1.0f, +1.0f };
	vertexBuffer[21].Pos = { -1.0f, -1.0f, +1.0f };
	vertexBuffer[22].Pos = { -1.0f, -1.0f, -1.0f };
	vertexBuffer[23].Pos = { +1.0f, -1.0f, -1.0f };

	vertexBuffer[20].Normal = { -0.0f, -1.0f, +0.0f };
	vertexBuffer[21].Normal = { -0.0f, -1.0f, +0.0f };
	vertexBuffer[22].Normal = { -0.0f, -1.0f, +0.0f };
	vertexBuffer[23].Normal = { -0.0f, -1.0f, +0.0f };

	vertexBuffer[20].Tangent = { -1.0f, +0.0f, -1.0f };
	vertexBuffer[21].Tangent = { -1.0f, +0.0f, -1.0f };
	vertexBuffer[22].Tangent = { -1.0f, +0.0f, -1.0f };
	vertexBuffer[23].Tangent = { -1.0f, +0.0f, -1.0f };

	for ( int i = 0; i < 24; ++i )
	{
		vertexBuffer[i].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	constexpr static const float stride = 1.0f / 6.0f;
	for ( int i = 0; i < 6; ++i )
	{
		tag_Vertex( &array )[4] = ( tag_Vertex( & )[4] )vertexBuffer[i * 4];

		float mul1 = ( float )i;
		float mul2 = ( float )( i + 1 );
		array[0].Tex = { stride * mul1, 0.0f };
		array[1].Tex = { stride * mul2, 0.0f };
		array[2].Tex = { stride * mul2, 1.0f };
		array[3].Tex = { stride * mul1, 1.0f };
	}

	indexBuffer =
	{
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10, 11,

		12, 13, 15,
		13, 14, 15,

		16, 17, 19,
		17, 18, 19,

		20, 21, 23,
		21, 22, 23
	};

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateSphere( String^ xName, int tessellation )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeSphere( vertexBuffer, indexBuffer, 2.0f, tessellation, false, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateGeosphere( String^ xName, int tessellation )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeGeoSphere( vertexBuffer, indexBuffer, 2.0f, tessellation, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateCylinder( String^ xName, int tessellation )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeCylinder( vertexBuffer, indexBuffer, 1.0f, 2.0f, tessellation, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateCone( String^ xName, int tessellation )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeCone( vertexBuffer, indexBuffer, 2.0f, 1.0f, tessellation, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateTorus( String^ xName, int tessellation, float thickness )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeTorus( vertexBuffer, indexBuffer, 2.0f, thickness, tessellation, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateTetrahedron( String^ xName )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeTetrahedron( vertexBuffer, indexBuffer, 1.0f, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateOctahedron( String^ xName )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeOctahedron( vertexBuffer, indexBuffer, 1.0f, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateDodecahedron( String^ xName )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeDodecahedron( vertexBuffer, indexBuffer, 1.0f, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateIcosahedron( String^ xName )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeIcosahedron( vertexBuffer, indexBuffer, 1.0f, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}

Mesh^ Mesh::CreateTeapot( String^ xName, int tessellation )
{
	vector<tag_Vertex> vertexBuffer;
	vector<UINT> indexBuffer;

	ComputeTeapot( vertexBuffer, indexBuffer, 1.0f, tessellation, false );

	auto mesh = gcnew Mesh( xName );
	mesh->Initialize( vertexBuffer, indexBuffer );
	return mesh;
}