#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// DXGI 기능을 수행하는 클래스입니다.
	/// </summary>
	public ref class Factory : Object, System::Collections::Generic::IEnumerable<Adapter^>
	{
		virtual System::Collections::IEnumerator^ GetEnumerator2() sealed = System::Collections::IEnumerable::GetEnumerator;

	internal:
		IDXGIFactory7* mDXGIFactory = nullptr;

	public:
		/// <summary>
		/// <see cref="Factory"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Factory();
		~Factory();
		!Factory();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> 인터페이스에서 구현 됨.) 어댑터 컬렉션 전체를 반복하는 열거자를 반환합니다.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<Adapter^>^ GetEnumerator();
	};
}