#pragma once

namespace FbxSDK
{
	/// <summary>
	/// FBX �� �����͸� �ҷ����� �ý����Դϴ�.
	/// </summary>
	public ref class Importer
	{
	internal:
		static FbxManager* mManager;
		static System::Object^ mLocker;

		FbxImporter* mImporter = nullptr;

	public:
		/// <summary>
		/// <see cref="Importer"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Importer();
		~Importer();
		!Importer();

		/// <summary>
		/// FBX ������ �ҷ��ɴϴ�.
		/// </summary>
		/// <param name="filepath"> �ҷ��� ���� ��θ� �����մϴ�. </param>
		Scene^ Import( System::String^ filepath );
	};
}