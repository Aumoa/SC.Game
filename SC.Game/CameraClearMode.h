#pragma once

namespace SC::Game
{
	/// <summary>
	/// 카메라의 초기화 모드를 표현합니다.
	/// </summary>
	public enum class CameraClearMode
	{
		/// <summary>
		/// 카메라를 초기화하지 않습니다.
		/// </summary>
		NoClear,

		/// <summary>
		/// 카메라를 단색으로 초기화합니다.
		/// </summary>
		SolidColor,

		/// <summary>
		/// 카메라를 지정된 스카이박스 텍스처로 초기화합니다.
		/// </summary>
		Skybox
	};
}