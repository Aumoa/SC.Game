#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// UI 위치의 상대적 고정점을 표현합니다.
	/// </summary>
	public enum class Anchor
	{
		/// <summary>
		/// 왼쪽 위 위치를 사용합니다.
		/// </summary>
		LeftTop = 0,

		/// <summary>
		/// 위쪽 가운데 위치를 사용합니다.
		/// </summary>
		Top = 1,

		/// <summary>
		/// 오른쪽 위 위치를 사용합니다.
		/// </summary>
		RightTop = 2,

		/// <summary>
		/// 왼쪽 가운데 위치를 사용합니다.
		/// </summary>
		Left = 3,

		/// <summary>
		/// 가운데 위치를 사용합니다.
		/// </summary>
		Center = 4,

		/// <summary>
		/// 오른쪽 가운데 위치를 사용합니다.
		/// </summary>
		Right = 5,

		/// <summary>
		/// 왼쪽 아래 위치를 사용합니다.
		/// </summary>
		LeftBottom = 6,

		/// <summary>
		/// 아래쪽 가운데 위치를 사용합니다.
		/// </summary>
		Bottom = 7,

		/// <summary>
		/// 오른쪽 아래 위치를 사용합니다.
		/// </summary>
		RightBottom = 8
	};
}