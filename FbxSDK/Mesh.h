#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 메쉬 형식의 속성 데이터를 표현합니다.
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
		/// 재질 색인 번호를 가져옵니다.
		/// </summary>
		property int MaterialIndex
		{
			int get();
		}

		/// <summary>
		/// 해당 메쉬가 스키닝 정점 버퍼를 사용하는지 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsSkinned
		{
			bool get();
		}

		/// <summary>
		/// 정점 버퍼를 가져옵니다.
		/// </summary>
		property cli::array<SC::Game::Vertex>^ VertexBuffer
		{
			cli::array<SC::Game::Vertex>^ get();
		}

		/// <summary>
		/// 스키닝 정점 버퍼를 가져옵니다.
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