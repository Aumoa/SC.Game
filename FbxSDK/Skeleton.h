#pragma once

namespace FbxSDK
{
	/// <summary>
	/// ���� ������ �Ӽ��� �����ɴϴ�.
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
		/// ������ ��ü �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
		/// <summary>
		/// ������ �̸��� ����, ���ӽ����̽� ���� �����ϰ� �����ɴϴ�.
		/// </summary>
		property System::String^ NameOnly
		{
			System::String^ get();
		}
	};
}