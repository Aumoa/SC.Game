#pragma once

namespace SC::Game
{
	/// <summary>
	/// 조명의 형태를 나타냅니다.
	/// </summary>
	public enum class LightType
	{
		/// <summary>
		/// 평행광을 나타냅니다.
		/// </summary>
		Directional,

		/// <summary>
		/// Spotlight를 나타냅니다.
		/// </summary>
		Spot,

		/// <summary>
		/// 점 형태의 조명을 나타냅니다.
		/// </summary>
		Point
	};
}