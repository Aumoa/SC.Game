using namespace SC;
using namespace SC::Game;

using namespace System;

void MeshRenderer::Render( CDeviceContext& deviceContext )
{
	auto meshFilter = GetComponent<MeshFilter^>();

	if ( meshFilter )
	{
		auto mesh = meshFilter->Mesh;

		if ( mesh )
		{
			// 개체의 트랜스폼을 설정합니다.
			deviceContext.SetGraphicsRootConstantBufferView( ( UINT )Slot_3D_Transform, Transform->mConstants->GetGPUVirtualAddress() );

			// 렌더러가 사용하는 재질을 설정합니다.
			auto mat = mMaterial;
			if ( mat == nullptr )
				mat = Game::Material::mDefault;
			mat->SetConstantBuffer( deviceContext );

			// 메쉬를 렌더링합니다.
			mesh->DrawIndexed( deviceContext );
		}
	}
}

MeshRenderer::MeshRenderer()
{

}

Object^ MeshRenderer::Clone()
{
	auto clone = gcnew MeshRenderer();
	clone->mMaterial = mMaterial;
	return clone;
}

Material^ MeshRenderer::Material::get()
{
	return mMaterial;
}

void MeshRenderer::Material::set( Game::Material^ value )
{
	mMaterial = value;
}