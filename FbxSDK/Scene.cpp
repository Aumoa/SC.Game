using namespace FbxSDK;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Numerics;
using namespace System::Threading;

Scene::Scene( FbxScene* scene )
{
	mScene = scene;

	mJoints = gcnew List<Joint>();
	mJointApplied = gcnew List<bool>();

	Monitor::Enter( Importer::mLocker );
	FbxGeometryConverter geometryConverter( Importer::mManager );
	geometryConverter.Triangulate( scene, true );
	geometryConverter.SplitMeshesPerMaterial( scene, true );

	FbxSystemUnit::m.ConvertScene( scene );
	Monitor::Exit( Importer::mLocker );

	mAnimStacks = gcnew cli::array<AnimStack^>( mScene->GetSrcObjectCount<FbxAnimStack>() );
	for ( int i = 0; i < mAnimStacks->Length; ++i )
	{
		auto animStack = mScene->GetSrcObject<FbxAnimStack>( i );
		auto animName = animStack->GetName();

		auto takeInfo = mScene->GetTakeInfo( animName );
		auto start = takeInfo->mLocalTimeSpan.GetStart().GetFrameCount( FbxTime::eFrames24 );
		auto end = takeInfo->mLocalTimeSpan.GetStop().GetFrameCount( FbxTime::eFrames24 );

		auto length = end - start;
		mAnimStacks[i] = gcnew AnimStack( animStack );
		mAnimStacks[i]->mTakeInfo = takeInfo;
		mAnimStacks[i]->mName = gcnew String( animName );
		mAnimStacks[i]->mTakeStart = start;
		mAnimStacks[i]->mTakeEnd = end;
		mAnimStacks[i]->mTakeLength = length;
	}

	mAnimationClips = gcnew cli::array<SC::Game::AnimationClip^>( mAnimStacks->Length );
	for ( int i = 0; i < mAnimationClips->Length; ++i )
	{
		mAnimationClips[i] = gcnew SC::Game::AnimationClip( mAnimStacks[i]->Name );
		mAnimationClips[i]->IsLoop = true;
	}

	ReadSkeletonHierarchy( scene->GetRootNode(), -1 );

	mRootNode = gcnew Node( this, scene->GetRootNode() );

	mMaterials = gcnew cli::array<Material^>( scene->GetMaterialCount() );
	for ( int i = 0; i < mMaterials->Length; ++i )
	{
		mMaterials[i] = gcnew Material( scene->GetMaterial( i ) );
	}
}

void Scene::Release()
{
	if ( mScene )
	{
		Monitor::Enter( Importer::mLocker );
		mScene->Destroy();
		mScene = nullptr;
		Monitor::Exit( Importer::mLocker );
	}
}

Node^ Scene::RootNode::get()
{
	return mRootNode;
}

int Scene::NumMaterials::get()
{
	return mMaterials->Length;
}

Material^ Scene::GetMaterial( int index )
{
	return mMaterials[index];
}

int Scene::NumAnimationClips::get()
{
	return mAnimationClips->Length;
}

SC::Game::AnimationClip^ Scene::GetAnimationClip( int index )
{
	return mAnimationClips[index];
}

IList<Joint>^ Scene::Joints::get()
{
	return mJoints;
}

void Scene::ReadSkeletonHierarchy( FbxNode* node, int parentIndex )
{
	auto attribute = node->GetNodeAttribute();
	auto name = gcnew String( node->GetName() );
	Joint joint;
	joint.ParentIndex = parentIndex;
	joint.Name = gcnew String( node->GetName() );
	joint.Offset = Matrix4x4::Identity;
	joint.Transform = Matrix4x4::Identity;

	parentIndex = mJoints->Count;
	mJoints->Add( joint );
	mJointApplied->Add( false );

	for ( int i = 0; i < node->GetChildCount(); ++i )
	{
		ReadSkeletonHierarchy( node->GetChild( i ), parentIndex );
	}
}