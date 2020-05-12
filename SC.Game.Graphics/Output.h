#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// 어댑터와 연결된 디스플레이에 대한 공통 기능을 수행합니다.
	/// </summary>
	public ref class Output : Object
	{
	internal:
		IDXGIOutput* mOutput = nullptr;

	internal:
		Output();

	public:
		~Output();
		!Output();

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 디스플레이의 정보를 조회하여 개체의 텍스트 형식을 생성하여 반환합니다.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// 현재 디스플레이 정보를 조회합니다.
		/// </summary>
		OutputQueryInfo QueryInfo();
	};
}