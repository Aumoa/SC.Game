#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 메쉬의 디포머를 표현합니다.
	/// </summary>
	public ref class Deformer
	{
	internal:
		fbxsdk::FbxDeformer* mDeformer = nullptr;
	};
}