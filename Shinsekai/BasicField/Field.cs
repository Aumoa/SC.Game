using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai.BasicField
{
	static class Field
	{
		public static IList<GameObject> enemys;

		static Field()
		{
			enemys = new List<GameObject>();
		}
	}
}
