#pragma once

namespace FbxSDK
{
	/// <summary>
	/// FBX 모델 데이터를 불러오는 시스템입니다.
	/// </summary>
	public ref class Importer
	{
	internal:
		static FbxManager* mManager;
		static System::Object^ mLocker;

		FbxImporter* mImporter = nullptr;

	public:
		/// <summary>
		/// <see cref="Importer"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Importer();
		~Importer();
		!Importer();

		/// <summary>
		/// FBX 파일을 불러옵니다.
		/// </summary>
		/// <param name="filepath"> 불러올 파일 경로를 전달합니다. </param>
		Scene^ Import( System::String^ filepath );
	};
}