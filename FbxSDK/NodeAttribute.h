#pragma once

namespace FbxSDK
{
	/// <summary>
	/// ����� �Ӽ��� ǥ���ϴ� ��ü�Դϴ�.
	/// </summary>
	public ref class NodeAttribute
	{
		FbxNodeAttribute* mNodeAttribute = nullptr;
		NodeAttributeType mType;

	internal:
		NodeAttribute( FbxNodeAttribute* nodeAttribute );

	public:
		/// <summary>
		/// �ش� ��� �Ӽ��� ������ �����ɴϴ�.
		/// </summary>
		property NodeAttributeType AttributeType
		{
			NodeAttributeType get();
		}
	};
}