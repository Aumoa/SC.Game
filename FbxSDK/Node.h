#pragma once

namespace FbxSDK
{
	/// <summary>
	/// FBX 모델의 단일 노드를 표현합니다.
	/// </summary>
	public ref class Node
	{
	internal:
		Scene^ mScene;
		fbxsdk::FbxNode* mNode = nullptr;

		cli::array<Node^>^ mChilds;

		NodeAttribute^ mDefaultAttribute;

		System::Numerics::Vector3 mPosition;
		System::Numerics::Vector3 mScale;
		System::Numerics::Quaternion mRotation;

		Skeleton^ mSkeleton;
		System::Collections::Generic::List<Mesh^> mMeshes;

	internal:
		Node( Scene^ sceneRef, fbxsdk::FbxNode* node );

	public:
		/// <summary>
		/// 해당 노드의 메쉬 개수를 가져옵니다.
		/// </summary>
		property int MeshCount
		{
			int get();
		}

		/// <summary>
		/// 노드의 메쉬 속서을 가져옵니다.
		/// </summary>
		/// <param name="index"> 노드 속성 인덱스를 전달합니다. </param>
		Mesh^ GetMeshAttribute( int index );

		/// <summary>
		/// 해당 노드의 뼈대 속성에 대한 데이터를 가져옵니다.
		/// </summary>
		Skeleton^ GetSkeleton();

		/// <summary>
		/// 해당 노드의 하위 노드 개수를 가져옵니다.
		/// </summary>
		property int NumChilds
		{
			int get();
		}

		/// <summary>
		/// 해당 노드의 하위 노드를 가져옵니다.
		/// </summary>
		/// <param name="index"> 하위 노드의 번호를 전달합니다. </param>
		Node^ GetChild( int index );

		/// <summary>
		/// 노드의 이름을 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}

		/// <summary>
		/// 메쉬의 기하 변환 위치를 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 Position
		{
			System::Numerics::Vector3 get();
		}

		/// <summary>
		/// 메쉬의 기하 변환 비례를 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 Scale
		{
			System::Numerics::Vector3 get();
		}

		/// <summary>
		/// 메쉬의 기하 변환 회전을 가져옵니다.
		/// </summary>
		property System::Numerics::Quaternion Rotation
		{
			System::Numerics::Quaternion get();
		}

	private:
		void ProcessAnimation();
		fbxsdk::FbxAMatrix GetGeometryTransformation();
	};
}