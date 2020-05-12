using namespace FbxSDK;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Numerics;

using namespace SC;
using namespace SC::Game;

using namespace System::Collections::Generic;

Node::Node( Scene^ sceneRef, fbxsdk::FbxNode* node )
{
	mScene = sceneRef;
	mNode = node;

	auto localTransform = mNode->EvaluateLocalTransform();
	Assign( mPosition, localTransform.GetT() );
	Assign( mScale, localTransform.GetS() );
	Assign( mRotation, localTransform.GetQ() );
	mRotation = Quaternion::Normalize( mRotation );

	mChilds = gcnew array<Node^>( node->GetChildCount() );
	for ( int i = 0; i < mChilds->Length; ++i )
	{
		mChilds[i] = gcnew Node( sceneRef, node->GetChild( i ) );
	}

	auto attributeCount = mNode->GetNodeAttributeCount();
	for ( int i = 0; i < attributeCount; ++i )
	{
		auto attribute = mNode->GetNodeAttributeByIndex( i );
		auto type = attribute->GetAttributeType();

		switch ( type )
		{
		case FbxNodeAttribute::eMesh:
			mMeshes.Add( gcnew Mesh( this, mNode, ( FbxMesh* )attribute ) );
			break;
		case FbxNodeAttribute::eSkeleton:
			mSkeleton = gcnew Skeleton( this, ( FbxSkeleton* )attribute );
			break;
		}
	}

	ProcessAnimation();
}

int Node::MeshCount::get()
{
	return mMeshes.Count;
}

FbxSDK::Mesh^ Node::GetMeshAttribute( int index )
{
	return mMeshes[index];
}

Skeleton^ Node::GetSkeleton()
{
	return mSkeleton;
}

int Node::NumChilds::get()
{
	return mChilds->Length;
}

Node^ Node::GetChild( int index )
{
	return mChilds[index];
}

String^ Node::Name::get()
{
	return gcnew String( mNode->GetName() );
}

Vector3 Node::Position::get()
{
	return mPosition;
}

Vector3 Node::Scale::get()
{
	return mScale;
}

Quaternion Node::Rotation::get()
{
	return mRotation;
}

void Node::ProcessAnimation()
{
	int numAnim = mScene->mAnimStacks->Length;
	auto nodeName = gcnew String( mNode->GetNameOnly() );

	constexpr float timeDelta = 1.0f / 24.0f;
	for ( int i = 0; i < numAnim; ++i )
	{
		auto animStack = mScene->mAnimStacks[i];
		auto animLayer = animStack->mAnimStack->GetMember<FbxAnimLayer>();
		auto animClip = mScene->mAnimationClips[i];

		Keyframes keyframes;
		keyframes.Translation = gcnew List<Keyframe>();
		keyframes.Scaling = gcnew List<Keyframe>();
		keyframes.Rotation = gcnew List<KeyframeQ>();

		for ( Int64 i = animStack->mTakeStart; i <= animStack->mTakeEnd; ++i )
		{
			FbxTime currTime;
			currTime.SetFrame( i, FbxTime::eFrames24 );

			auto globalTransform = mNode->EvaluateLocalTransform( currTime );

			auto T = globalTransform.GetT();
			auto S = globalTransform.GetS();
			auto Q = globalTransform.GetQ();

			Keyframe t;
			t.TimePos = timeDelta * ( float )i;
			Assign( t.Value, T );

			Keyframe s;
			s.TimePos = timeDelta * ( float )i;
			Assign( s.Value, S );

			KeyframeQ q;
			q.TimePos = timeDelta * ( float )i;
			Assign( q.Value, Q );

			//t.Value = Vector3::Zero;
			//s.Value = Vector3::One;
			//q.Value = Quaternion::Identity;

			keyframes.Translation->Add( t );
			keyframes.Scaling->Add( s );
			keyframes.Rotation->Add( q );
		}

		if ( !animClip->HasKeyframes( nodeName ) )
		{
			animClip->AddKeyframes( nodeName, keyframes );
		}
	}
}

fbxsdk::FbxAMatrix Node::GetGeometryTransformation()
{
	auto T = mNode->GetGeometricTranslation( FbxNode::eSourcePivot );
	auto R = mNode->GetGeometricRotation( FbxNode::eSourcePivot );
	auto S = mNode->GetGeometricScaling( FbxNode::eSourcePivot );

	return FbxAMatrix( T, R, S );
}