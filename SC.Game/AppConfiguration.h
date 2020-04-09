#pragma once

namespace SC::Game
{
	/// <summary>
	/// 게임 앱 환경 설정을 표현합니다.
	/// </summary>
	public value struct AppConfiguration
	{
	internal:
		System::String^ mAdapterName;

	public:
		/// <summary>
		/// 앱의 이름을 설정하거나 가져옵니다.
		/// </summary>
		System::String^ AppName;

		/// <summary>
		/// 초당 물리 연산 횟수를 설정하거나 가져옵니다.
		/// </summary>
		int PhysicsUpdatesPerSecond;

		/// <summary>
		/// 앱의 수직 동기화 기능 활성화 상태를 나타내는 값을 설정하거나 가져옵니다.
		/// </summary>
		bool VSync;

	public:
		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 현재 개체의 텍스트 표현을 생성하여 반환합니다.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// 시스템에서 사용하는 그래픽 어댑터의 간단한 정보를 가져옵니다.
		/// </summary>
		property System::String^ AdapterName
		{
			System::String^ get();
		}
	};
}