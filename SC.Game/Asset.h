#pragma once

namespace SC::Game
{
	/// <summary>
	/// 게임 데이터 자산을 표현합니다.
	/// </summary>
	public ref class Asset
	{
		System::String^ mName;

	protected:
		/// <summary>
		/// <see cref="Asset"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 식별자 이름을 전달합니다. </param>
		Asset( System::String^ xName );

	public:
		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 개체의 간단한 정보를 텍스트 형식으로 생성하여 반환합니다.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// 식별자 이름을 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
	};
}