#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� �� ���� ���ۿ� ���� �⺻ �Լ��� �����մϴ�.
	/// </summary>
	public ref class Mesh : public Asset
	{
	internal:
		ImmutableHeap* mVertexBuffer = nullptr;
		ImmutableHeap* mIndexBuffer = nullptr;

		UINT mVertexStride = 0;
		physx::PxConvexMesh* mConvexMesh = nullptr;
		physx::PxTriangleMesh* mTriangleMesh = nullptr;

		int mVertexCount = 0;
		int mIndexCount = 0;
		bool mIsSkinned = false;

	private:
		void Initialize( const void* pVertexBuffer, unsigned int vertexStride, const unsigned int* pIndexBuffer, unsigned int vertexCount, unsigned int indexCount );

	internal:
		Mesh( System::String^ xName );

		void Initialize( const std::vector<tag_Vertex>& vertexBuffer, const std::vector<unsigned int>& indexBuffer );
		void Initialize( const std::vector<tag_SkinnedVertex>& vertexBuffer, const std::vector<unsigned int>& indexBuffer );
		void DrawIndexed( CDeviceContext& deviceContext );
		void DrawSkinnedIndexed( UINT64 virtualAddress, CDeviceContext& deviceContext );

	public:
		~Mesh();
		!Mesh();

		/// <summary>
		/// ���� ��ü�� ��Ű�� �����͸� ����ϴ��� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsSkinned
		{
			bool get();
		}

		/// <summary>
		/// ���� �� ���� ������ ����� �̿��Ͽ� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="vertexBuffer"> ���� ���� ����� �����մϴ�. </param>
		/// <param name="indexBuffer"> ���� ���� ����� �����մϴ�. </param>
		static Mesh^ CreateMesh( System::String^ xName, System::Collections::Generic::IList<Vertex>^ vertexBuffer, System::Collections::Generic::IList<System::UInt32>^ indexBuffer );

		/// <summary>
		/// ���� �� ���� ������ ����� �̿��Ͽ� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="vertexBuffer"> ���� ���� ����� �����մϴ�. </param>
		/// <param name="indexBuffer"> ���� ���� ����� �����մϴ�. </param>
		static Mesh^ CreateMesh( System::String^ xName, System::Collections::Generic::IList<SkinnedVertex>^ vertexBuffer, System::Collections::Generic::IList<System::UInt32>^ indexBuffer );

		/// <summary>
		/// ��� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="texScaleX"> �ؽ�ó ��ǥ X�� ��ʸ� �����մϴ�. </param>
		/// <param name="texScaleX"> �ؽ�ó ��ǥ Y�� ��ʸ� �����մϴ�. </param>
		/// <param name="gridCountX"> ����� ���� X�� ������ �����մϴ�. </param>
		/// <param name="gridCountY"> ����� ���� Y�� ������ �����մϴ�. </param>
		static Mesh^ CreatePlane( System::String^ xName, float texScaleX, float texScaleY, int gridCountX, int gridCountY );

		/// <summary>
		/// ��� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="texScaleX"> �ؽ�ó ��ǥ X�� ��ʸ� �����մϴ�. </param>
		/// <param name="texScaleX"> �ؽ�ó ��ǥ Y�� ��ʸ� �����մϴ�. </param>
		static Mesh^ CreatePlane( System::String^ xName, float texScaleX, float texScaleY )
		{
			return CreatePlane( xName, texScaleX, texScaleY, 1, 1 );
		}

		/// <summary>
		/// ��� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		static Mesh^ CreatePlane( System::String^ xName )
		{
			return CreatePlane( xName, 1.0f, 1.0f );
		}

		/// <summary>
		/// ������ü �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		static Mesh^ CreateCube( System::String^ xName );

		/// <summary>
		/// ���� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="tessellation"> �޽��� �׼����̼� Ƚ���� �����մϴ�. </param>
		static Mesh^ CreateSphere( System::String^ xName, int tessellation );

		/// <summary>
		/// ���� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="tessellation"> �޽��� �׼����̼� Ƚ���� �����մϴ�. </param>
		static Mesh^ CreateGeosphere( System::String^ xName, int tessellation );

		/// <summary>
		/// ���� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="tessellation"> �޽��� �׼����̼� Ƚ���� �����մϴ�. </param>
		static Mesh^ CreateCylinder( System::String^ xName, int tessellation );

		/// <summary>
		/// ���� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="tessellation"> �޽��� �׼����̼� Ƚ���� �����մϴ�. </param>
		static Mesh^ CreateCone( System::String^ xName, int tessellation );

		/// <summary>
		/// ��ȯ�� �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="tessellation"> �޽��� �׼����̼� Ƚ���� �����մϴ�. </param>
		/// <param name="thickness"> ���⸦ �����մϴ�. </param>
		static Mesh^ CreateTorus( System::String^ xName, int tessellation, float thickness );

		/// <summary>
		/// ���ü �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		static Mesh^ CreateTetrahedron( System::String^ xName );

		/// <summary>
		/// �ȸ�ü �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		static Mesh^ CreateOctahedron( System::String^ xName );

		/// <summary>
		/// ���̸�ü �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		static Mesh^ CreateDodecahedron( System::String^ xName );

		/// <summary>
		/// �̽ʸ�ü �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		static Mesh^ CreateIcosahedron( System::String^ xName );

		/// <summary>
		/// �̽ʸ�ü �޽� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="xName"> ������ ��ü �̸��� �����մϴ�. </param>
		/// <param name="tessellation"> �޽��� �׼����̼� Ƚ���� �����մϴ�. </param>
		static Mesh^ CreateTeapot( System::String^ xName, int tessellation );
	};
}