#pragma once

namespace FbxSDK
{
	/// <summary>
	/// FBX 모델 데이터에 대한 장면을 표현합니다.
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
		/// 장면에 포함된 모든 데이터를 제거합니다.
		/// </summary>
		void Release();

		/// <summary>
		/// 이 장면의 루트 노드를 가져옵니다.
		/// </summary>
		property Node^ RootNode
		{
			Node^ get();
		}

		/// <summary>
		/// 장면에 포함 된 재질 개체의 개수를 가져옵니다.
		/// </summary>
		property int NumMaterials
		{
			int get();
		}

		/// <summary>
		/// 재질 개체를 가져옵니다.
		/// </summary>
		/// <param name="index"> 색인 번호를 전달합니다. </param>
		Material^ GetMaterial( int index );

		/// <summary>
		/// 애니메이션 클립 개수를 가져옵니다.
		/// </summary>
		property int NumAnimationClips
		{
			int get();
		}

		/// <summary>
		/// 애니메이션 클립을 가져옵니다.
		/// </summary>
		/// <param name="index"> 애니메이션 클립 인덱스를 전달합니다. </param>
		SC::Game::AnimationClip^ GetAnimationClip( int index );

		/// <summary>
		/// 뼈대 목록을 가져옵니다.
		/// </summary>
		property System::Collections::Generic::IList<Joint>^ Joints
		{
			System::Collections::Generic::IList<Joint>^ get();
		}

	private:
		void ReadSkeletonHierarchy( FbxNode* node, int parentIndex );
	};
}