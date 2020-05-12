using namespace FbxSDK;

using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;
using namespace System::Collections::Generic;

using namespace std;

using _Mesh = FbxSDK::Mesh;

_Mesh::Mesh( Node^ nodeRef, FbxNode* node, FbxMesh* mesh )
{
	mNodeRef = nodeRef;
	mNode = node;
	mMesh = mesh;

	ReadControlPoints();
	ReadSkinnedPair();

	bool hasNormal = mesh->GetElementNormalCount() > 0;
	bool hasTangent = mesh->GetElementTangentCount() > 0;
	bool hasUV = mesh->GetElementUVCount() > 0;
	bool hasColor = mesh->GetElementVertexColorCount() > 0;

	auto normals = hasNormal ? mesh->GetElementNormal() : nullptr;
	auto tangents = hasTangent ? mesh->GetElementTangent() : nullptr;
	auto uvs = hasUV ? mesh->GetElementUV() : nullptr;
	auto colors = hasColor ? mesh->GetElementVertexColor() : nullptr;

	auto polygonCount = mesh->GetPolygonCount();

	auto geometryTransform1 = GetGeometryTransformation( node );
	Matrix4x4 geometryTransform;
	::Assign( geometryTransform, geometryTransform1 );

	if ( mIsSkinned )
	{
		mSkinnedVertexBuffer = gcnew cli::array<SkinnedVertex>( polygonCount * 3 );
		for ( int i = 0, vertexCounter = 0; i < polygonCount; ++i )
		{
			for ( int j = 0; j < 3; ++j )
			{
				SkinnedVertex v;

				auto controlPointIndex = mesh->GetPolygonVertex( i, j );

				::Assign( v.Pos, mSkinnedControlPoints[controlPointIndex].ControlPoint );
				Assign( v.Weights, mSkinnedControlPoints[controlPointIndex].BlendingInfos );
				Assign( v.Indices, mSkinnedControlPoints[controlPointIndex].BlendingInfos );
				::Assign( v.Normal, ReadLayer( normals, controlPointIndex, vertexCounter ) );
				::Assign( v.Tangent, ReadLayer( tangents, controlPointIndex, vertexCounter ) );
				if ( uvs )
				{
					auto uvIndex = uvs->GetMappingMode() == FbxGeometryElement::eByPolygonVertex ? mesh->GetTextureUVIndex( ( int )i, ( int )j ) : vertexCounter;
					Assign( v.Tex, ReadLayerUV( uvs, controlPointIndex, uvIndex ) );
					v.Tex.Y = 1.0f - v.Tex.Y;
				}
				Assign( v.Color, ReadLayer( colors, controlPointIndex, vertexCounter ) );

				v.Pos = Vector3::Transform( v.Pos, geometryTransform );
				v.Normal = Vector3::TransformNormal( v.Normal, geometryTransform );
				v.Tangent = Vector3::TransformNormal( v.Tangent, geometryTransform );

				mSkinnedVertexBuffer[vertexCounter] = v;
				vertexCounter += 1;
			}
		}
	}
	else
	{
		mVertexBuffer = gcnew cli::array<Vertex>( polygonCount * 3 );
		for ( int i = 0, vertexCounter = 0; i < polygonCount; ++i )
		{
			for ( int j = 0; j < 3; ++j )
			{
				Vertex v;

				auto controlPointIndex = mesh->GetPolygonVertex( i, j );
				::Assign( v.Pos, mSkinnedControlPoints[controlPointIndex].ControlPoint );
				::Assign( v.Normal, ReadLayer( normals, controlPointIndex, vertexCounter ) );
				::Assign( v.Tangent, ReadLayer( tangents, controlPointIndex, vertexCounter ) );
				if ( uvs )
				{
					auto uvIndex = uvs->GetMappingMode() == FbxGeometryElement::eByPolygonVertex ? mesh->GetTextureUVIndex( ( int )i, ( int )j ) : vertexCounter;
					Assign( v.Tex, ReadLayerUV( uvs, controlPointIndex, uvIndex ) );
					v.Tex.Y = 1.0f - v.Tex.Y;
				}
				Assign( v.Color, ReadLayer( colors, controlPointIndex, vertexCounter ) );

				v.Pos = Vector3::Transform( v.Pos, geometryTransform );
				v.Normal = Vector3::TransformNormal( v.Normal, geometryTransform );
				v.Tangent = Vector3::TransformNormal( v.Tangent, geometryTransform );

				mVertexBuffer[vertexCounter] = v;
				vertexCounter += 1;
			}
		}
	}

	FbxLayerElementArrayTemplate<int>* materialIndices = nullptr;
	if ( mesh->GetMaterialIndices( &materialIndices ) )
	{
		auto count = materialIndices->GetCount();
		mMaterialIndex = materialIndices->GetAt( 0 );
	}
}

_Mesh::~Mesh()
{
	this->!Mesh();
}

_Mesh::!Mesh()
{
	if ( mSkinnedControlPoints )
	{
		delete[] mSkinnedControlPoints;
		mSkinnedControlPoints = nullptr;
	}
}

int _Mesh::MaterialIndex::get()
{
	return mMaterialIndex;
}

bool _Mesh::IsSkinned::get()
{
	return mIsSkinned;
}

cli::array<Vertex>^ _Mesh::VertexBuffer::get()
{
	return mVertexBuffer;
}

cli::array<SkinnedVertex>^ _Mesh::SkinnedVertexBuffer::get()
{
	return mSkinnedVertexBuffer;
}

void _Mesh::ReadControlPoints()
{
	auto controlPoints = mMesh->GetControlPoints();

	mSkinnedControlPoints = new SkinnedControlPoint[mMesh->GetControlPointsCount()];
	for ( int i = 0; i < mMesh->GetControlPointsCount(); ++i )
	{
		mSkinnedControlPoints[i].ControlPoint = controlPoints[i];
	}
}

void _Mesh::ReadSkinnedPair()
{
	auto node = mNode;
	int numDeformers = mMesh->GetDeformerCount();
	auto geometryTransform = GetGeometryTransformation( node );

	for ( int i = 0; i < numDeformers; ++i )
	{
		FbxSkin* currSkin = ( FbxSkin* )mMesh->GetDeformer( i, FbxDeformer::eSkin );
		if ( !currSkin ) continue;

		int numClusters = currSkin->GetClusterCount();
		for ( int j = 0; j < numClusters; ++j )
		{
			auto* currCluster = currSkin->GetCluster( j );
			String^ currJointName = gcnew String( currCluster->GetLink()->GetName() );
			String^ nodeName = gcnew String( node->GetName() );
			int currJointIndex = SearchJointIndex( currJointName );
			auto linkNode = currCluster->GetLink();

			fbxsdk::FbxAMatrix transformMatrix;
			fbxsdk::FbxAMatrix transformLinkMatrix;
			fbxsdk::FbxAMatrix globalBindposeInverseMatrix;

			currCluster->GetTransformMatrix( transformMatrix );
			currCluster->GetTransformLinkMatrix( transformLinkMatrix );
			globalBindposeInverseMatrix = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;

			auto mScene = mNodeRef->mScene;
			Joint joint = mScene->mJoints[currJointIndex];
			bool applied = mScene->mJointApplied[currJointIndex];
			if ( applied )
			{
				// 새로운 뼈대를 생성합니다.
				currJointIndex = mScene->mJoints->Count;

				// 새 뼈대를 목록에 추가합니다.
				mScene->mJoints->Add( joint );
				mScene->mJointApplied->Add( false );
			}

			// 뼈대 오프셋 행렬을 설정합니다.
			::Assign( joint.Offset, globalBindposeInverseMatrix );
			joint.Link = mNodeRef;
			::Assign( joint.Transform, transformLinkMatrix );

			mScene->mJoints[currJointIndex] = joint;
			mScene->mJointApplied[currJointIndex] = true;

			int numIndices = currCluster->GetControlPointIndicesCount();
			for ( int k = 0; k < numIndices; ++k )
			{
				auto controlPointIndex = currCluster->GetControlPointIndices()[k];
				auto& cp = mSkinnedControlPoints[controlPointIndex];
				pair<float, int> blendingInfo;
				blendingInfo.first = ( float )currCluster->GetControlPointWeights()[k];
				blendingInfo.second = currJointIndex;
				cp.BlendingInfos.push_back( blendingInfo );

				mIsSkinned = true;
			}
		}
	}
}

int _Mesh::SearchJointIndex( String^ jointName )
{
	auto mScene = mNodeRef->mScene;

	for ( int i = 0; i < mScene->mJoints->Count; ++i )
	{
		if ( mScene->mJoints[i].Name == jointName )
		{
			return i;
		}
	}

	return -1;
}

fbxsdk::FbxAMatrix _Mesh::GetGeometryTransformation( FbxNode* node )
{
	auto T = node->GetGeometricTranslation( FbxNode::eSourcePivot );
	auto R = node->GetGeometricRotation( FbxNode::eSourcePivot );
	auto S = node->GetGeometricScaling( FbxNode::eSourcePivot );

	return FbxAMatrix( T, R, S );
}

void _Mesh::Assign( Vector2% left, fbxsdk::FbxVector2& right )
{
	left.X = ( float )right[0];
	left.Y = ( float )right[1];
}

void _Mesh::Assign( Vector4% left, fbxsdk::FbxColor& right )
{
	left.X = ( float )right.mRed;
	left.Y = ( float )right.mGreen;
	left.Z = ( float )right.mBlue;
	left.W = ( float )right.mAlpha;
}

void _Mesh::Assign( Vector3% left, const vector<pair<float, int>>& blendingInfos )
{
	int size = ( int )blendingInfos.size();

	if ( size >= 1 ) left.X = blendingInfos[0].first;
	if ( size >= 2 ) left.Y = blendingInfos[1].first;
	if ( size >= 3 ) left.Z = blendingInfos[2].first;
}

void _Mesh::Assign( BoneIndices% left, const vector<pair<float, int>>& blendingInfos )
{
	int size = ( int )blendingInfos.size();

	if ( size >= 1 ) left.X = blendingInfos[0].second;
	if ( size >= 2 ) left.Y = blendingInfos[1].second;
	if ( size >= 3 ) left.Z = blendingInfos[2].second;
	if ( size >= 4 ) left.W = blendingInfos[3].second;
}

int _Mesh::GetDirectIndex( FbxLayerElementTemplate<FbxVector4>* layer, int controlPointIndex, int vertexCounter )
{
	auto mappingMode = layer->GetMappingMode();
	auto referenceMode = layer->GetReferenceMode();

	int mappingIndex{ };
	if ( mappingMode == FbxGeometryElement::eByControlPoint )
		mappingIndex = controlPointIndex;
	else if ( mappingMode == FbxGeometryElement::eByPolygonVertex )
		mappingIndex = vertexCounter;

	int directIndex{ };
	if ( referenceMode == FbxGeometryElement::eDirect )
		directIndex = mappingIndex;
	else if ( referenceMode == FbxGeometryElement::eIndexToDirect )
		directIndex = layer->GetIndexArray().GetAt( mappingIndex );

	return directIndex;
}

int _Mesh::GetDirectIndex( FbxLayerElementTemplate<FbxColor>* layer, int controlPointIndex, int vertexCounter )
{
	auto mappingMode = layer->GetMappingMode();
	auto referenceMode = layer->GetReferenceMode();

	int mappingIndex{ };
	if ( mappingMode == FbxGeometryElement::eByControlPoint )
		mappingIndex = controlPointIndex;
	else if ( mappingMode == FbxGeometryElement::eByPolygonVertex )
		mappingIndex = vertexCounter;

	int directIndex{ };
	if ( referenceMode == FbxGeometryElement::eDirect )
		directIndex = mappingIndex;
	else if ( referenceMode == FbxGeometryElement::eIndexToDirect )
		directIndex = layer->GetIndexArray().GetAt( mappingIndex );

	return directIndex;
}

int _Mesh::GetDirectIndexUV( FbxLayerElementTemplate<FbxVector2>* layer, int controlPointIndex, int vertexCountOrTextureIndex )
{
	auto mappingMode = layer->GetMappingMode();
	auto referenceMode = layer->GetReferenceMode();

	int mappingIndex{ };
	if ( mappingMode == FbxGeometryElement::eByControlPoint )
		mappingIndex = controlPointIndex;
	else if ( mappingMode == FbxGeometryElement::eByPolygonVertex )
		return vertexCountOrTextureIndex;

	int directIndex{ };
	if ( referenceMode == FbxGeometryElement::eDirect )
		directIndex = mappingIndex;
	else if ( referenceMode == FbxGeometryElement::eIndexToDirect )
		directIndex = layer->GetIndexArray().GetAt( mappingIndex );

	return directIndex;
}

FbxVector4 _Mesh::ReadLayer( FbxLayerElementTemplate<FbxVector4>* layer, int controlPointIndex, int vertexCounter )
{
	if ( layer )
	{
		auto directIndex = GetDirectIndex( layer, controlPointIndex, vertexCounter );
		decltype( auto ) directArray = layer->GetDirectArray();
		return directArray.GetAt( directIndex );
	}
	else
	{
		return FbxVector4();
	}
}

FbxVector2 _Mesh::ReadLayerUV( FbxLayerElementTemplate<FbxVector2>* layer, int controlPointIndex, int vertexCountOrTextureIndex )
{
	if ( layer )
	{
		auto directIndex = GetDirectIndexUV( layer, controlPointIndex, vertexCountOrTextureIndex );
		decltype( auto ) directArray = layer->GetDirectArray();
		return directArray.GetAt( directIndex );
	}
	else
	{
		return FbxVector2();
	}
}

FbxColor _Mesh::ReadLayer( FbxLayerElementTemplate<FbxColor>* layer, int controlPointIndex, int vertexCounter )
{
	if ( layer )
	{
		auto directIndex = GetDirectIndex( layer, controlPointIndex, vertexCounter );
		decltype( auto ) directArray = layer->GetDirectArray();
		return directArray.GetAt( directIndex );
	}
	else
	{
		return FbxColor( 1.0, 1.0, 1.0 );
	}
}