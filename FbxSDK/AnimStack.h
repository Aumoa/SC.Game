#pragma once

namespace FbxSDK
{
	/// <summary>
	/// ���� �ִϸ��̼� ������ ǥ���մϴ�.
	/// </summary>
	public ref class AnimStack
	{
	internal:
		FbxAnimStack* mAnimStack = nullptr;
		FbxTakeInfo* mTakeInfo = nullptr;

		System::String^ mName;
		System::Int64 mTakeStart;
		System::Int64 mTakeEnd;
		System::Int64 mTakeLength;

	internal:
		AnimStack( FbxAnimStack* animStack );

	public:
		/// <summary>
		/// �ִϸ��̼� ������ �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
	};
}