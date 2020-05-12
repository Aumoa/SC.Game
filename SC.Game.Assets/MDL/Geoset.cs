using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets.MDL
{
	struct Geoset
	{
		public Vector3[] Vertices;
		public Vector3[] Normals;
		public Vector2[] TexCoords;
		public int[] VertexGroups;
		public int[][] Faces;
		public Group[] Groups;
		public int MaterialID;
	}
}
