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

		int mVertexCount = 0;
		int mIndexCount = 0;
		bool mIsSkinned = false;

	private:
		void Initialize( const void* pVertexBuffer, unsigned int vertexStride, const unsigned int* pIndexBuffer, unsigned int vertexCount, unsigned int indexCount );

	internal:
		Mesh( System::String^ xName );

		void Initialize( const std::vector<Vertex>& vertexBuffer, const std::vector<unsigned int>& indexBuffer );
		void Initialize( const std::vector<SkinnedVertex>& vertexBuffer, const std::vector<unsigned int>& indexBuffer );
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
	};
}