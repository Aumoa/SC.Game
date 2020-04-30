using System;
using SC.Game;

namespace THHourai
{
	[Flags]
	enum CustomTag
	{
		CameraBlocker = Tag.Custom << 1,
		Terrain = Tag.Custom << 2,
	}
}