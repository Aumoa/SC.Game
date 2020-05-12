#pragma once

namespace FbxSDK
{
	/// <summary>
	/// FBX �� �����Ϳ� ���� ����� ǥ���մϴ�.
	/// </summary>
	public ref class Scene
	{
	internal:
		FbxScene* mScene = nullptr;
		Node^ mRootNode;

		cli::array<Material^>^ mMaterials;
		System::Collections::Generic::List<Joint>^ mJoints;
		System::Collections::Generic::List<bool>^ mJointApplied;

		cli::array<AnimStack^>^ mAnimStacks;
		cli::array<SC::Game::AnimationClip^>^ mAnimationClips;

	internal:
		Scene( FbxScene* scene );

	public:
		/// <summary>
		/// ��鿡 ���Ե� ��� �����͸� �����մϴ�.
		/// </summary>
		void Release();

		/// <summary>
		/// �� ����� ��Ʈ ��带 �����ɴϴ�.
		/// </summary>
		property Node^ RootNode
		{
			Node^ get();
		}

		/// <summary>
		/// ��鿡 ���� �� ���� ��ü�� ������ �����ɴϴ�.
		/// </summary>
		property int NumMaterials
		{
			int get();
		}

		/// <summary>
		/// ���� ��ü�� �����ɴϴ�.
		/// </summary>
		/// <param name="index"> ���� ��ȣ�� �����մϴ�. </param>
		Material^ GetMaterial( int index );

		/// <summary>
		/// �ִϸ��̼� Ŭ�� ������ �����ɴϴ�.
		/// </summary>
		property int NumAnimationClips
		{
			int get();
		}

		/// <summary>
		/// �ִϸ��̼� Ŭ���� �����ɴϴ�.
		/// </summary>
		/// <param name="index"> �ִϸ��̼� Ŭ�� �ε����� �����մϴ�. </param>
		SC::Game::AnimationClip^ GetAnimationClip( int index );

		/// <summary>
		/// ���� ����� �����ɴϴ�.
		/// </summary>
		property System::Collections::Generic::IList<Joint>^ Joints
		{
			System::Collections::Generic::IList<Joint>^ get();
		}

	private:
		void ReadSkeletonHierarchy( FbxNode* node, int parentIndex );
	};
}