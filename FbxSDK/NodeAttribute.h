#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 노드의 속성을 표현하는 개체입니다.
	/// </summary>
	public ref class NodeAttribute
	{
		FbxNodeAttribute* mNodeAttribute = nullptr;
		NodeAttributeType mType;

	internal:
		NodeAttribute( FbxNodeAttribute* nodeAttribute );

	public:
		/// <summary>
		/// 해당 노드 속성의 유형을 가져옵니다.
		/// </summary>
		property NodeAttributeType AttributeType
		{
			NodeAttributeType get();
		}
	};
}