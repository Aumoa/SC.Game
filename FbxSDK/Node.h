#pragma once

namespace FbxSDK
{
	/// <summary>
	/// FBX ���� ���� ��带 ǥ���մϴ�.
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
		/// �ش� ����� �޽� ������ �����ɴϴ�.
		/// </summary>
		property int MeshCount
		{
			int get();
		}

		/// <summary>
		/// ����� �޽� �Ӽ��� �����ɴϴ�.
		/// </summary>
		/// <param name="index"> ��� �Ӽ� �ε����� �����մϴ�. </param>
		Mesh^ GetMeshAttribute( int index );

		/// <summary>
		/// �ش� ����� ���� �Ӽ��� ���� �����͸� �����ɴϴ�.
		/// </summary>
		Skeleton^ GetSkeleton();

		/// <summary>
		/// �ش� ����� ���� ��� ������ �����ɴϴ�.
		/// </summary>
		property int NumChilds
		{
			int get();
		}

		/// <summary>
		/// �ش� ����� ���� ��带 �����ɴϴ�.
		/// </summary>
		/// <param name="index"> ���� ����� ��ȣ�� �����մϴ�. </param>
		Node^ GetChild( int index );

		/// <summary>
		/// ����� �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}

		/// <summary>
		/// �޽��� ���� ��ȯ ��ġ�� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 Position
		{
			System::Numerics::Vector3 get();
		}

		/// <summary>
		/// �޽��� ���� ��ȯ ��ʸ� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 Scale
		{
			System::Numerics::Vector3 get();
		}

		/// <summary>
		/// �޽��� ���� ��ȯ ȸ���� �����ɴϴ�.
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