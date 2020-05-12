using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assimp;

namespace SC.Game.Assets.Assimp
{
	struct Joint
	{
		public string Name;
		public Matrix4x4 Offset;
		public int Parent;
	}
}
