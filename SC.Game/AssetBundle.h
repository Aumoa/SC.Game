#pragma once

namespace SC::Game
{
	/// <summary>
	/// 게임 데이터 자산에 대한 인터페이스를 제공합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class AssetBundle sealed abstract
	{
	public:
		/// <summary>
		/// 데이터 자산을 비동기로 불러옵니다.
		/// </summary>
		/// <param name="filepath"> 파일 경로를 전달합니다. </param>
		static System::Threading::Tasks::Task<GameObject^>^ LoadAssetAsync( System::String^ filepath );

	internal:
		static GameObject^ CreateGameObjectFromMDL( System::String^ filepath );
	};
}