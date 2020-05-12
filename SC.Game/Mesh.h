#pragma once

namespace SC::Game
{
	/// <summary>
	/// 정점 및 색인 버퍼에 대한 기본 함수를 제공합니다.
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
		/// 현재 개체가 스키닝 데이터를 사용하는지 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsSkinned
		{
			bool get();
		}

		/// <summary>
		/// 정점 및 색인 데이터 목록을 이용하여 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="vertexBuffer"> 정점 버퍼 목록을 전달합니다. </param>
		/// <param name="indexBuffer"> 색인 버퍼 목록을 전달합니다. </param>
		static Mesh^ CreateMesh( System::String^ xName, System::Collections::Generic::IList<Vertex>^ vertexBuffer, System::Collections::Generic::IList<System::UInt32>^ indexBuffer );

		/// <summary>
		/// 정점 및 색인 데이터 목록을 이용하여 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="vertexBuffer"> 정점 버퍼 목록을 전달합니다. </param>
		/// <param name="indexBuffer"> 색인 버퍼 목록을 전달합니다. </param>
		static Mesh^ CreateMesh( System::String^ xName, System::Collections::Generic::IList<SkinnedVertex>^ vertexBuffer, System::Collections::Generic::IList<System::UInt32>^ indexBuffer );

		/// <summary>
		/// 평면 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="texScaleX"> 텍스처 좌표 X축 비례를 전달합니다. </param>
		/// <param name="texScaleX"> 텍스처 좌표 Y축 비례를 전달합니다. </param>
		/// <param name="gridCountX"> 평면의 격자 X축 개수를 전달합니다. </param>
		/// <param name="gridCountY"> 평면의 격자 Y축 개수를 전달합니다. </param>
		static Mesh^ CreatePlane( System::String^ xName, float texScaleX, float texScaleY, int gridCountX, int gridCountY );

		/// <summary>
		/// 평면 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="texScaleX"> 텍스처 좌표 X축 비례를 전달합니다. </param>
		/// <param name="texScaleX"> 텍스처 좌표 Y축 비례를 전달합니다. </param>
		static Mesh^ CreatePlane( System::String^ xName, float texScaleX, float texScaleY )
		{
			return CreatePlane( xName, texScaleX, texScaleY, 1, 1 );
		}

		/// <summary>
		/// 평면 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		static Mesh^ CreatePlane( System::String^ xName )
		{
			return CreatePlane( xName, 1.0f, 1.0f );
		}

		/// <summary>
		/// 직육면체 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		static Mesh^ CreateCube( System::String^ xName );

		/// <summary>
		/// 구형 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="tessellation"> 메쉬의 테셀레이션 횟수를 전달합니다. </param>
		static Mesh^ CreateSphere( System::String^ xName, int tessellation );

		/// <summary>
		/// 구형 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="tessellation"> 메쉬의 테셀레이션 횟수를 전달합니다. </param>
		static Mesh^ CreateGeosphere( System::String^ xName, int tessellation );

		/// <summary>
		/// 원통 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="tessellation"> 메쉬의 테셀레이션 횟수를 전달합니다. </param>
		static Mesh^ CreateCylinder( System::String^ xName, int tessellation );

		/// <summary>
		/// 원뿔 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="tessellation"> 메쉬의 테셀레이션 횟수를 전달합니다. </param>
		static Mesh^ CreateCone( System::String^ xName, int tessellation );

		/// <summary>
		/// 원환면 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="tessellation"> 메쉬의 테셀레이션 횟수를 전달합니다. </param>
		/// <param name="thickness"> 굵기를 전달합니다. </param>
		static Mesh^ CreateTorus( System::String^ xName, int tessellation, float thickness );

		/// <summary>
		/// 사면체 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		static Mesh^ CreateTetrahedron( System::String^ xName );

		/// <summary>
		/// 팔면체 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		static Mesh^ CreateOctahedron( System::String^ xName );

		/// <summary>
		/// 십이면체 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		static Mesh^ CreateDodecahedron( System::String^ xName );

		/// <summary>
		/// 이십면체 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		static Mesh^ CreateIcosahedron( System::String^ xName );

		/// <summary>
		/// 이십면체 메쉬 개체를 생성합니다.
		/// </summary>
		/// <param name="xName"> 데이터 개체 이름을 전달합니다. </param>
		/// <param name="tessellation"> 메쉬의 테셀레이션 횟수를 전달합니다. </param>
		static Mesh^ CreateTeapot( System::String^ xName, int tessellation );
	};
}