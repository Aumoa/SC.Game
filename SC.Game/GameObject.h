#pragma once

namespace SC::Game
{
	/// <summary>
	/// 장면에 포함될 수 있는, 게임 세계에서 표현되는 모든 개체의 공통 인터페이스를 제공합니다.
	/// </summary>
	public ref class GameObject
	{
		System::String^ mName;

	public:
		/// <summary>
		/// <see cref="GameObject"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체의 식별 이름을 전달합니다. </param>
		GameObject( System::String^ xName );

		/// <summary>
		/// 개체의 식별 이름을 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
	};
}