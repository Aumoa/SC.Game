#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// ���÷��� ȸ�� ��带 ǥ���մϴ�.
	/// </summary>
	public enum class RotationMode
	{
		/// <summary>
		/// �� �� ���� ���Դϴ�. �Ϲ������� �� ���� �����Դϴ�.
		/// </summary>
		Unspecified = 0,

		/// <summary>
		/// ȸ�� ������ ��Ÿ���ϴ�.
		/// </summary>
		Identity = 1,

		/// <summary>
		/// 90�� ȸ���� ��Ÿ���ϴ�.
		/// </summary>
		Rotate90 = 2,

		/// <summary>
		/// 180�� ȸ���� ��Ÿ���ϴ�.
		/// </summary>
		Rotate180 = 3,

		/// <summary>
		/// 270�� ȸ���� ��Ÿ���ϴ�.
		/// </summary>
		Rotate270 = 4
	};
}