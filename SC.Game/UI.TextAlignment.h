#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 텍스트 정렬 방식을 표현합니다.
	/// </summary>
	public enum class TextAlignment
	{
		/// <summary>
		/// 텍스트를 왼쪽으로 정렬합니다.
		/// </summary>
		Left = 0,

		/// <summary>
		/// 텍스트를 가운데로 정렬합니다.
		/// </summary>
		Center = 1,

		/// <summary>
		/// 텍스트를 오른쪽으로 정렬합니다.
		/// </summary>
		Right = 2,

		/// <summary>
		/// 텍스트를 여백 없이 정렬합니다.
		/// </summary>
		Justified = 3
	};
}