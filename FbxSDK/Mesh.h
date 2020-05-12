#pragma once

namespace FbxSDK
{
	/// <summary>
	/// �޽� ������ �Ӽ� �����͸� ǥ���մϴ�.
	/// </summary>
	public ref class Mesh
	{
	internal:
		Node^ mNodeRef;
		FbxNode* mNode = nullptr;
		FbxMesh* mMesh = nullptr;

		cli::array<SC::Game::Vertex>^ mVertexBuffer;
		cli::array<SC::Game::SkinnedVertex>^ mSkinnedVertexBuffer;
		int mMaterialIndex = -1;
		bool mIsSkinned = false;

		SkinnedControlPoint* mSkinnedControlPoints = nullptr;

	internal:
		Mesh( Node^ nodeRef, FbxNode* node, FbxMesh* mesh );

	public:
		~Mesh();
		!Mesh();

		/// <summary>
		/// ���� ���� ��ȣ�� �����ɴϴ�.
		/// </summary>
		property int MaterialIndex
		{
			int get();
		}

		/// <summary>
		/// �ش� �޽��� ��Ű�� ���� ���۸� ����ϴ��� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsSkinned
		{
			bool get();
		}

		/// <summary>
		/// ���� ���۸� �����ɴϴ�.
		/// </summary>
		property cli::array<SC::Game::Vertex>^ VertexBuffer
		{
			cli::array<SC::Game::Vertex>^ get();
		}

		/// <summary>
		/// ��Ű�� ���� ���۸� �����ɴϴ�.
		/// </summary>
		property cli::array<SC::Game::SkinnedVertex>^ SkinnedVertexBuffer
		{
			cli::array<SC::Game::SkinnedVertex>^ get();
		}

	private:
		void ReadControlPoints();
		void ReadSkinnedPair();
		int SearchJointIndex( System::String^ jointName );

		fbxsdk::FbxAMatrix GetGeometryTransformation( FbxNode* node );

		static void Assign( System::Numerics::Vector2% left, fbxsdk::FbxVector2& right );
		static void Assign( System::Numerics::Vector4% left, fbxsdk::FbxColor& right );
		static void Assign( System::Numerics::Vector3% left, const std::vector<std::pair<float, int>>& skinnedInfos );
		static void Assign( SC::Game::BoneIndices% left, const std::vector<std::pair<float, int>>& skinnedInfos );

		static int GetDirectIndex( FbxLayerElementTemplate<FbxVector4>* layer, int controlPointIndex, int vectorCounter );
		static int GetDirectIndex( FbxLayerElementTemplate<FbxColor>* layer, int controlPointIndex, int vectorCounter );
		static int GetDirectIndexUV( FbxLayerElementTemplate<FbxVector2>* layer, int controlPointIndex, int vertexCountOrTextureIndex );

		static FbxVector4 ReadLayer( FbxLayerElementTemplate<FbxVector4>* element, int controlPointIndex, int vertexCounter );
		static FbxVector2 ReadLayerUV( FbxLayerElementTemplate<FbxVector2>* layer, int controlPointIndex, int vertexCountOrTextureIndex );
		static FbxColor ReadLayer( FbxLayerElementTemplate<FbxColor>* layer, int controlPointIndex, int vertexCount );
	};
}