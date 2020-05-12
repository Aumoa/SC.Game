#pragma once

#include <fbxsdk.h>
#include <msclr/marshal.h>
#include <vector>
#include <string>
#include <map>

using namespace fbxsdk;

#include "NodeAttributeType.h"
#include "TimeMode.h"

namespace FbxSDK
{
	struct SkinnedControlPoint;
	value struct JointPair;
	value struct Joint;

	ref class Importer;
	ref class Scene;
	ref class Node;
	ref class NodeAttribute;
	ref class Mesh;
	ref class Material;
	ref class Deformer;
	ref class Skin;
	ref class Skeleton;
	ref class AnimStack;
}

inline void Assign( System::Numerics::Vector3% left, fbxsdk::FbxVector4& right )
{
	left.X = ( float )right[0];
	left.Y = ( float )right[1];
	left.Z = ( float )right[2];
}

inline void Assign( System::Numerics::Quaternion% left, fbxsdk::FbxQuaternion& right )
{
	left.X = ( float )right[0];
	left.Y = ( float )right[1];
	left.Z = ( float )right[2];
	left.W = ( float )right[3];
}

inline void Assign( System::Numerics::Quaternion% left, fbxsdk::FbxVector4& right )
{
	left.X = ( float )right[0];
	left.Y = ( float )right[1];
	left.Z = ( float )right[2];
	left.W = ( float )right[3];
}

inline void Assign( System::Numerics::Matrix4x4% left, fbxsdk::FbxAMatrix& right )
{
	left.M11 = ( float )right.Get( 0, 0 );
	left.M12 = ( float )right.Get( 0, 1 );
	left.M13 = ( float )right.Get( 0, 2 );
	left.M14 = ( float )right.Get( 0, 3 );

	left.M21 = ( float )right.Get( 1, 0 );
	left.M22 = ( float )right.Get( 1, 1 );
	left.M23 = ( float )right.Get( 1, 2 );
	left.M24 = ( float )right.Get( 1, 3 );

	left.M31 = ( float )right.Get( 2, 0 );
	left.M32 = ( float )right.Get( 2, 1 );
	left.M33 = ( float )right.Get( 2, 2 );
	left.M34 = ( float )right.Get( 2, 3 );

	left.M41 = ( float )right.Get( 3, 0 );
	left.M42 = ( float )right.Get( 3, 1 );
	left.M43 = ( float )right.Get( 3, 2 );
	left.M44 = ( float )right.Get( 3, 3 );
}

inline void Assign( fbxsdk::FbxAMatrix& left, System::Numerics::Matrix4x4% right )
{
	left[0][0] = ( double )right.M11;
	left[0][1] = ( double )right.M12;
	left[0][2] = ( double )right.M13;
	left[0][3] = ( double )right.M14;

	left[1][0] = ( double )right.M21;
	left[1][1] = ( double )right.M22;
	left[1][2] = ( double )right.M23;
	left[1][3] = ( double )right.M24;

	left[2][0] = ( double )right.M31;
	left[2][1] = ( double )right.M32;
	left[2][2] = ( double )right.M33;
	left[2][3] = ( double )right.M34;

	left[3][0] = ( double )right.M41;
	left[3][1] = ( double )right.M42;
	left[3][2] = ( double )right.M43;
	left[3][3] = ( double )right.M44;
}

#include "SkinnedControlPoint.h"
#include "Joint.h"

#include "Importer.h"
#include "Scene.h"
#include "Node.h"
#include "NodeAttribute.h"
#include "Mesh.h"
#include "Material.h"
#include "Deformer.h"
#include "Skin.h"
#include "Skeleton.h"
#include "AnimStack.h"