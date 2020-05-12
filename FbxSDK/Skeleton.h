#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 뼈대 형식의 속성을 가져옵니다.
	/// </summary>
	public ref class Skeleton
	{
	internal:
		Node^ mNodeRef;

		System::String^ mName;
		System::String^ mNameOnly;

	internal:
		Skeleton( Node^ nodeRef, FbxSkeleton* skeleton );

	public:
		/// <summary>
		/// 뼈대의 전체 이름을 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
		/// <summary>
		/// 뼈대의 이름을 공백, 네임스페이스 등을 제외하고 가져옵니다.
		/// </summary>
		property System::String^ NameOnly
		{
			System::String^ get();
		}
	};
}