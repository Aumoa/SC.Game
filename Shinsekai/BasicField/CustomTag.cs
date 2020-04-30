using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai.BasicField
{
	enum CustomTag
	{
		Terrain = Tag.Custom << 1,
		AbilityTarget = Terrain << 1,
	}
}
