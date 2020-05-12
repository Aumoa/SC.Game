#pragma once

namespace FbxSDK
{
	struct SkinnedControlPoint
	{
		FbxVector4 ControlPoint;
		std::vector<std::pair<float, int>> BlendingInfos;

		SkinnedControlPoint()
		{
			ControlPoint = FbxVector4( 0.0f, 0.0f, 0.0f, 0.0f );
		}
	};
}