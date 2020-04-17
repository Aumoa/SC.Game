using namespace SC;
using namespace SC::Game;

using namespace System;

void SkinnedMeshRenderer::Skinning( CDeviceContext& deviceContext )
{
	if ( mMesh )
	{
		auto vertexCount = mMesh->mVertexCount;

		deviceContext.SetComputeRootShaderResourceView( Slot_Skinning_SkinnedVertexBuffer, mMesh->mVertexBuffer->GetGPUVirtualAddress() );
		deviceContext.SetComputeRootUnorderedAccessView( Slot_Skinning_VertexBuffer, mVertexBuffer->GetGPUVirtualAddress() );
		deviceContext.SetComputeRoot32BitConstant( Slot_Skinning_SkinningConstants, vertexCount, 0 );

		int dispatch = ( vertexCount - 1 ) / 32 + 1;
		deviceContext.Dispatch( dispatch, 1 );
	}
}

void SkinnedMeshRenderer::Render( CDeviceContext& deviceContext )
{
	if ( mMesh )
	{
		auto material = mMaterial;
		if ( material == nullptr ) material = Game::Material::mDefault;

		mMesh->DrawSkinnedIndexed( mVertexBuffer->GetGPUVirtualAddress(), deviceContext );
	}
}

SkinnedMeshRenderer::SkinnedMeshRenderer()
{

}

SkinnedMeshRenderer::~SkinnedMeshRenderer()
{
	this->!SkinnedMeshRenderer();
}

SkinnedMeshRenderer::!SkinnedMeshRenderer()
{
	if ( mVertexBuffer )
	{
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}
}

Object^ SkinnedMeshRenderer::Clone()
{
	auto clone = gcnew SkinnedMeshRenderer();
	clone->mMaterial = mMaterial;
	clone->Mesh = mMesh;
	return clone;
}

Mesh^ SkinnedMeshRenderer::Mesh::get()
{
	return mMesh;
}

void SkinnedMeshRenderer::Mesh::set( Game::Mesh^ value )
{
	mMesh = value;

	if ( mVertexBuffer )
	{
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}

	mVertexBuffer = new LargeHeap( D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, sizeof( Vertex ) * mMesh->mVertexCount );
}

Material^ SkinnedMeshRenderer::Material::get()
{
	return mMaterial;
}

void SkinnedMeshRenderer::Material::set( Game::Material^ value )
{
	mMaterial = value;
}