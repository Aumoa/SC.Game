#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� �±׸� ǥ���մϴ�.
	/// </summary>
	[System::Flags]
	public enum class Tag
	{
		/// <summary>
		/// �⺻ ���� �±׸� ��Ÿ���ϴ�.
		/// </summary>
		Default = 0b0,

		/// <summary>
		/// ����� ���� ���� �±��� ���� ��ġ�� ��Ÿ���ϴ�.
		/// </summary>
		Custom = 0b10,

		/// <summary>
		/// ��� �±� ������ ��Ÿ���ϴ�.
		/// </summary>
		All = -1
	};
}