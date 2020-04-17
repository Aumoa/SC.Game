#pragma once

namespace SC::Game
{
	/// <summary>
	/// ī�޶��� �ʱ�ȭ ��带 ǥ���մϴ�.
	/// </summary>
	public enum class CameraClearMode
	{
		/// <summary>
		/// ī�޶� �ʱ�ȭ���� �ʽ��ϴ�.
		/// </summary>
		NoClear,

		/// <summary>
		/// ī�޶� �ܻ����� �ʱ�ȭ�մϴ�.
		/// </summary>
		SolidColor,

		/// <summary>
		/// ī�޶� ������ ��ī�̹ڽ� �ؽ�ó�� �ʱ�ȭ�մϴ�.
		/// </summary>
		Skybox
	};
}