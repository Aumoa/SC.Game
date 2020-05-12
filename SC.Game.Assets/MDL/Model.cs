using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace SC.Game.Assets.MDL
{
	struct Model
	{
		public string Name;
		public int NumGeosets;
		public int NumGeosetAnims;
		public int NumHelpers;
		public int NumBones;
		public int NumAttachments;
		public int BlendTime;
		public Vector3 MinimumExtent;
		public Vector3 MaximumExtent;
	}
}
