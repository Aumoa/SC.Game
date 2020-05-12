#pragma once

namespace FbxSDK
{
	/// <summary>
	/// ���븦 ǥ���մϴ�.
	/// </summary>
	public value struct Joint
	{
		/// <summary>
		/// �ش� ������ �θ� ������ ���� ��ȣ�� ǥ���մϴ�.
		/// </summary>
		/// <remarks>
		/// ������ ���� ��ȣ�� <see cref="System::Collections::Generic::List"/> ������ �÷��ǿ����� ���� ��ȣ�� �����մϴ�.
		/// </remarks>
		int ParentIndex;

		/// <summary>
		/// ������ �̸��� ǥ���մϴ�.
		/// </summary>
		System::String^ Name;

		/// <summary>
		/// ������ ������ ��ȯ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Matrix4x4 Offset;

		/// <summary>
		/// ������ ��ġ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Matrix4x4 Transform;

		/// <summary>
		/// ������ ���� �޽��� ǥ���մϴ�.
		/// </summary>
		Node^ Link;

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) ���� ��ü�� �ؽ�Ʈ ǥ���� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override
		{
			return System::String::Format( "{0} -> {1}", ParentIndex, Name );
		}
	};
}