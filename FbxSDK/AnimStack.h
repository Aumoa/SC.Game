#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 단일 애니메이션 스택을 표현합니다.
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
		/// 애니메이션 스택의 이름을 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
	};
}