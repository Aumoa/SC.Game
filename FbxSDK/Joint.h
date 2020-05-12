#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 뼈대를 표현합니다.
	/// </summary>
	public value struct Joint
	{
		/// <summary>
		/// 해당 뼈대의 부모 뼈대의 색인 번호를 표현합니다.
		/// </summary>
		/// <remarks>
		/// 뼈대의 색인 번호는 <see cref="System::Collections::Generic::List"/> 구조의 컬렉션에서의 색인 번호와 동일합니다.
		/// </remarks>
		int ParentIndex;

		/// <summary>
		/// 뼈대의 이름을 표현합니다.
		/// </summary>
		System::String^ Name;

		/// <summary>
		/// 뼈대의 오프셋 변환을 표현합니다.
		/// </summary>
		System::Numerics::Matrix4x4 Offset;

		/// <summary>
		/// 뼈대의 위치를 표현합니다.
		/// </summary>
		System::Numerics::Matrix4x4 Transform;

		/// <summary>
		/// 뼈대의 참조 메쉬를 표현합니다.
		/// </summary>
		Node^ Link;

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 현재 개체의 텍스트 표현을 생성하여 반환합니다.
		/// </summary>
		System::String^ ToString() override
		{
			return System::String::Format( "{0} -> {1}", ParentIndex, Name );
		}
	};
}