#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 노드의 속성 유형을 표현합니다.
	/// </summary>
	public enum class NodeAttributeType
	{
		/// <summary>
		/// 알 수 없는 유형입니다.
		/// </summary>
		Unknown,

		/// <summary>
		/// 빈 속성 유형입니다.
		/// </summary>
		Null,

		/// <summary>
		/// 마커 형식의 속성 유형입니다.
		/// </summary>
		Marker,

		/// <summary>
		/// 뼈대 형식의 속성 유형입니다.
		/// </summary>
		Skeleton,

		/// <summary>
		/// 메쉬 형태의 속성 유형입니다.
		/// </summary>
		Mesh,
	};
}