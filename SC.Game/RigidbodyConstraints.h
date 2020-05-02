#pragma once

namespace SC::Game
{
	/// <summary>
	/// ������ٵ� ��ü�� ���� ���࿡ ���� �÷��׸� ��Ÿ���ϴ�.
	/// </summary>
	[System::Flags]
	public enum class RigidbodyConstraints
	{
		/// <summary>
		/// �ƹ��� ������ �����ϴ�.
		/// </summary>
		None = 0b00000000,

		/// <summary>
		/// X ��ġ���� �����˴ϴ�.
		/// </summary>
		PositionX = 0b00000001,

		/// <summary>
		/// Y ��ġ���� �����˴ϴ�.
		/// </summary>
		PositionY = 0b00000010,

		/// <summary>
		/// Z ��ġ���� �����˴ϴ�.
		/// </summary>
		PositionZ = 0b00000100,

		/// <summary>
		/// X ȸ������ �����˴ϴ�.
		/// </summary>
		RotationX = 0b00001000,

		/// <summary>
		/// Y ȸ������ �����˴ϴ�.
		/// </summary>
		RotationY = 0b00010000,

		/// <summary>
		/// Z ȸ������ �����˴ϴ�.
		/// </summary>
		RotationZ = 0b00100000,

		/// <summary>
		/// ��� ��ġ���� �����˴ϴ�.
		/// </summary>
		Position = 0b00000111,

		/// <summary>
		/// ��� ȸ������ �����˴ϴ�.
		/// </summary>
		Rotation = 0b00111000,

		/// <summary>
		/// ��� ���� �����˴ϴ�.
		/// </summary>
		All = 0b00111111
	};
}