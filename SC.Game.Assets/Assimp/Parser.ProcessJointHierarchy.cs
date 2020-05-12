using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using Assimp;
using Assimp.Unmanaged;

using SDK = Assimp;
using Quaternion = System.Numerics.Quaternion;

namespace SC.Game.Assets.Assimp
{
	partial class Parser
	{
		void ProcessJointHierarchy( GameObject gameObject, Node aiNode, int jointParent )
		{
			string name = aiNode.Name;

			var go = new GameObject( name );

			var jointIndex = SearchJoint( name );
			if ( jointIndex == -1 )
			{
				Joint joint1 = new Joint
				{
					Name = name,
					Offset = aiNode.Transform
				};
				joint1.Offset.Inverse();

				jointIndex = joints.Count;
				joints.Add( joint1 );
			}

			var joint = joints[jointIndex];
			joint.Parent = jointParent;

			Assign( out var left, joint.Offset );

			var bone = go.AddComponent<Bone>();
			bone.Index = jointIndex;
			bone.Name = name;
			bone.Offset = left;

			go.Transform.Parent = gameObject.Transform;

			for ( int i = 0; i < aiNode.ChildCount; ++i )
			{
				ProcessJointHierarchy( go, aiNode.Children[i], jointIndex );
			}
		}
	}
}
