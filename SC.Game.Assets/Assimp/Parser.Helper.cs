using System;
using System.Collections.Generic;
using System.Diagnostics.Tracing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using Assimp;

using SDK = Assimp;

namespace SC.Game.Assets.Assimp
{
	partial class Parser
	{
		int SearchJoint( string name )
		{
			for ( int i = 0; i < joints.Count; ++i )
			{
				if ( joints[i].Name == name )
				{
					return i;
				}
			}

			return -1;
		}

		void AddJointIndex( ref SkinnedVertex v, int jointIndex, float weight )
		{
			if ( v.Weights.X == 0.0f )
			{
				v.Indices.X = jointIndex;
				v.Weights.X = weight;
			}
			else if ( v.Weights.Y == 0.0f )
			{
				v.Indices.Y = jointIndex;
				v.Weights.Y = weight;
			}
			else if ( v.Weights.Z == 0.0f )
			{
				v.Indices.Z = jointIndex;
				v.Weights.Z = weight;
			}
			else
			{
				v.Indices.W = jointIndex;
			}
		}

		float Average( Color4D color )
		{
			return ( color.R + color.G + color.B ) / 3.0f;
		}

		void Assign( out Vector3 left, Vector3D right )
		{
			left.X = right.X;
			left.Y = right.Y;
			left.Z = right.Z;
		}

		void Assign( out Vector2 left, Vector3D right )
		{
			left.X = right.X;
			left.Y = right.Y;
		}

		void Assign( out Vector4 left, Color4D right )
		{
			left.X = right.R;
			left.Y = right.G;
			left.Z = right.B;
			left.W = right.A;
		}

		void Assign( out System.Numerics.Quaternion left, SDK.Quaternion right )
		{
			left.X = right.X;
			left.Y = right.Y;
			left.Z = right.Z;
			left.W = right.W;
		}

		void Assign( out System.Numerics.Matrix4x4 left, SDK.Matrix4x4 right )
		{
			left.M11 = right.A1;
			left.M12 = right.A2;
			left.M13 = right.A3;
			left.M14 = right.A4;

			left.M21 = right.B1;
			left.M22 = right.B2;
			left.M23 = right.B3;
			left.M24 = right.B4;

			left.M31 = right.C1;
			left.M32 = right.C2;
			left.M33 = right.C3;
			left.M34 = right.C4;

			left.M41 = right.D1;
			left.M42 = right.D2;
			left.M43 = right.D3;
			left.M44 = right.D4;
		}	}
}
