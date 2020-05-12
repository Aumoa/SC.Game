using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets.MDL
{
	struct Keyframes<T>
	{
		public string Method;
		public List<Keyframe<T>> Keys;
	}
}
