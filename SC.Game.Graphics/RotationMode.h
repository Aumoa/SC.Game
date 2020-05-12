#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// 디스플레이 회전 모드를 표현합니다.
	/// </summary>
	public enum class RotationMode
	{
		/// <summary>
		/// 알 수 없는 값입니다. 일반적으로 이 값을 오류입니다.
		/// </summary>
		Unspecified = 0,

		/// <summary>
		/// 회전 없음을 나타냅니다.
		/// </summary>
		Identity = 1,

		/// <summary>
		/// 90도 회전을 나타냅니다.
		/// </summary>
		Rotate90 = 2,

		/// <summary>
		/// 180도 회전을 나타냅니다.
		/// </summary>
		Rotate180 = 3,

		/// <summary>
		/// 270도 회전을 나타냅니다.
		/// </summary>
		Rotate270 = 4
	};
}