#pragma once

namespace SC::Game
{
	/// <summary>
	/// 캐릭터가 충돌할 때의 충돌 상태를 정의합니다.
	/// </summary>
	public enum class CharacterCollisionFlags
	{
		/// <summary>
		/// 캐릭터의 옆 부분이 충돌되었습니다.
		/// </summary>
		Sides = 0b1,
		
		/// <summary>
		/// 캐릭터의 윗 부분이 충돌되었습니다.
		/// </summary>
		Up = 0b10,

		/// <summary>
		/// 캐릭터의 밑 부분이 충돌되었습니다.
		/// </summary>
		Down = 0b100,
	};
}