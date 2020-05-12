#pragma once

namespace FbxSDK
{
	/// <summary>
	/// �ð� ��带 ��Ÿ���ϴ�.
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