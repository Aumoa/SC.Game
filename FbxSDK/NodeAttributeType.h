#pragma once

namespace FbxSDK
{
	/// <summary>
	/// ����� �Ӽ� ������ ǥ���մϴ�.
	/// </summary>
	public enum class NodeAttributeType
	{
		/// <summary>
		/// �� �� ���� �����Դϴ�.
		/// </summary>
		Unknown,

		/// <summary>
		/// �� �Ӽ� �����Դϴ�.
		/// </summary>
		Null,

		/// <summary>
		/// ��Ŀ ������ �Ӽ� �����Դϴ�.
		/// </summary>
		Marker,

		/// <summary>
		/// ���� ������ �Ӽ� �����Դϴ�.
		/// </summary>
		Skeleton,

		/// <summary>
		/// �޽� ������ �Ӽ� �����Դϴ�.
		/// </summary>
		Mesh,
	};
}