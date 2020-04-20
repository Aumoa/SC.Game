#pragma once

namespace SC::Game
{
	/// <summary>
	/// 게임 태그를 표현합니다.
	/// </summary>
	[System::Flags]
	public enum class Tag
	{
		/// <summary>
		/// 기본 게임 태그를 나타냅니다.
		/// </summary>
		Default = 0b0,

		/// <summary>
		/// 사용자 지정 게임 태그의 시작 위치를 나타냅니다.
		/// </summary>
		Custom = 0b10,

		/// <summary>
		/// 모든 태그 유형을 나타냅니다.
		/// </summary>
		All = -1
	};
}