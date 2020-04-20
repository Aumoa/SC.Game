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
		// 개체의 트랜스폼을 설정합니다.
		deviceContext.SetGraphicsRootConstantBufferView( ( UINT )Slot_3D_Transform, Transform->mConstants->GetGPUVirtualAddress() );

		// 렌더러가 사용하는 재질을 설정합니다.
		auto mat = mMaterial;
		if ( mat == nullptr )
			mat = Game::Material::mDefault;
		mat->SetConstantBuffer( deviceContext );

		// 메쉬를 렌더링합니다.
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