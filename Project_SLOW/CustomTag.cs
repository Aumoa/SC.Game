using System;
using System.Collections.Generic;
using System.Text;
using Project_SLOW.Stage1;
using SC.Game;

namespace Project_SLOW
{
	enum CustomTag
	{
		Terrain = Tag.Custom << 1,
		AbilityTarget = Terrain << 1
	}
}
