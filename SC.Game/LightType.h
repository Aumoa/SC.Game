#pragma once

namespace SC::Game
{
	/// <summary>
	/// ������ ���¸� ��Ÿ���ϴ�.
	/// </summary>
	public enum class LightType
	{
		/// <summary>
		/// ���౤�� ��Ÿ���ϴ�.
		/// </summary>
		Directional,

		/// <summary>
		/// Spotlight�� ��Ÿ���ϴ�.
		/// </summary>
		Spot,

		/// <summary>
		/// �� ������ ������ ��Ÿ���ϴ�.
		/// </summary>
		Point
	};
}