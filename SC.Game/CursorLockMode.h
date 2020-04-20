#pragma once

namespace SC::Game
{
	/// <summary>
	/// 커서 잠금 모드를 표현합니다.
	/// </summary>
	public enum class CursorLockMode
	{
		/// <summary>
		/// 커서 잠금 모드를 설정하지 않습니다.
		/// </summary>
		None,

		/// <summary>
		/// 커서를 화면 가운데로 잠급니다.
		/// </summary>
		Locked,

		/// <summary>
		/// 커서를 게임 창으로 가둡니다.
		/// </summary>
		Confined
	};
}