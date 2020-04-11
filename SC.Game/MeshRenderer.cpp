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
			// ��ü�� Ʈ�������� �����մϴ�.
			deviceContext.SetGraphicsRootConstantBufferView( ( UINT )Slot_3D_Transform, Transform->mConstants->GetGPUVirtualAddress() );

			// �������� ����ϴ� ������ �����մϴ�.

			// �޽��� �������մϴ�.
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
	return clone;
}