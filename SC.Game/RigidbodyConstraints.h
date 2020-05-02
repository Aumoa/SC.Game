#pragma once

namespace SC::Game
{
	/// <summary>
	/// 리지드바디 개체의 강제 제약에 대한 플래그를 나타냅니다.
	/// </summary>
	[System::Flags]
	public enum class RigidbodyConstraints
	{
		/// <summary>
		/// 아무런 제약이 없습니다.
		/// </summary>
		None = 0b00000000,

		/// <summary>
		/// X 위치값이 고정됩니다.
		/// </summary>
		PositionX = 0b00000001,

		/// <summary>
		/// Y 위치값이 고정됩니다.
		/// </summary>
		PositionY = 0b00000010,

		/// <summary>
		/// Z 위치값이 고정됩니다.
		/// </summary>
		PositionZ = 0b00000100,

		/// <summary>
		/// X 회전값이 고정됩니다.
		/// </summary>
		RotationX = 0b00001000,

		/// <summary>
		/// Y 회전값이 고정됩니다.
		/// </summary>
		RotationY = 0b00010000,

		/// <summary>
		/// Z 회전값이 고정됩니다.
		/// </summary>
		RotationZ = 0b00100000,

		/// <summary>
		/// 모든 위치값이 고정됩니다.
		/// </summary>
		Position = 0b00000111,

		/// <summary>
		/// 모든 회전값이 고정됩니다.
		/// </summary>
		Rotation = 0b00111000,

		/// <summary>
		/// 모든 값이 고정됩니다.
		/// </summary>
		All = 0b00111111
	};
}