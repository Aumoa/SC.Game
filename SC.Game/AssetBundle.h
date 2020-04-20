#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ������ �ڻ꿡 ���� �������̽��� �����մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class AssetBundle sealed abstract
	{
	public:
		/// <summary>
		/// ������ �ڻ��� �񵿱�� �ҷ��ɴϴ�.
		/// </summary>
		/// <param name="filepath"> ���� ��θ� �����մϴ�. </param>
		static System::Threading::Tasks::Task<GameObject^>^ LoadAssetAsync( System::String^ filepath );

	internal:
		static GameObject^ CreateGameObjectFromMDL( System::String^ filepath );
	};
}