#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 메쉬의 표면 스킨을 표현합니다.
	/// </summary>
	public ref class Skin
	{
	internal:
		fbxsdk::FbxSkin* mSkin = nullptr;
	};
}