#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// 시스템에 존재하는 물리 어댑터 또는 소프트웨어 구현 어댑터에 대한 기능을 제공합니다.
	/// </summary>
	public ref class Adapter : Object, System::Collections::Generic::IEnumerable<Output^>
	{
		virtual System::Collections::IEnumerator^ GetEnumerator2() sealed = System::Collections::IEnumerable::GetEnumerator;

	internal:
		IDXGIAdapter1* mAdapter = nullptr;

	internal:
		Adapter();

	public:
		~Adapter();
		!Adapter();

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 디스플레이의 정보를 조회하여 개체의 텍스트 형식을 생성하여 반환합니다.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> 인터페이스에서 구현 됨.) 출력 디스플레이 컬렉션 전체를 반복하는 열거자를 반환합니다.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<Output^>^ GetEnumerator();

		/// <summary>
		/// 어댑터 정보를 조회합니다.
		/// </summary>
		AdapterInfo QueryInfo();
	};
}