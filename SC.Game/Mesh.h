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
		/// ���� ��ü�� ��Ű�� �����͸� ����ϴ��� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsSkinned
		{
			bool get();
		}

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
	};
}