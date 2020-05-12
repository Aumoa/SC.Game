#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 시간 모드를 나타냅니다.
	/// </summary>
	public enum class TimeMode
	{
		DefaultMode,
		Frames120,
		Frames100,
		Frames60,
		Frames50,
		Frames48,
		Frames30,
		Frames30Drop,
		NTSCDropFrame,
		NTSCFullFrame,
		PAL,
		Frames24,
		Frames1000,
		FilmFullFrame,
		Custom,
		Frames96,
		Frames72,
		Frames59dot94
	};
}