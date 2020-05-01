#pragma once

namespace SC::Game
{
	/// <summary>
	/// ĳ���Ͱ� �浹�� ���� �浹 ���¸� �����մϴ�.
	/// </summary>
	public enum class CharacterCollisionFlags
	{
		/// <summary>
		/// ĳ������ �� �κ��� �浹�Ǿ����ϴ�.
		/// </summary>
		Sides = 0b1,
		
		/// <summary>
		/// ĳ������ �� �κ��� �浹�Ǿ����ϴ�.
		/// </summary>
		Up = 0b10,

		/// <summary>
		/// ĳ������ �� �κ��� �浹�Ǿ����ϴ�.
		/// </summary>
		Down = 0b100,
	};
}