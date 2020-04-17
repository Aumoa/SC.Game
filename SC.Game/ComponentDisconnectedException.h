#pragma once

namespace SC::Game
{
	/// <summary>
	/// 컴포넌트가 사용되었지만 게임 개체와 연결되지 않았거나 연결이 종료되었을 경우 발생하는 예외입니다.
	/// </summary>
	public ref class ComponentDisconnectedException : public System::Exception
	{
	public:
		/// <summary>
		/// 기본 예외 메시지를 사용하여 <see cref="ComponentDisconnectedException"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		ComponentDisconnectedException( System::Object^ sender );
	};
}