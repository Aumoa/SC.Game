#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// DXGI ����� �����ϴ� Ŭ�����Դϴ�.
	/// </summary>
	public ref class Factory : Object, System::Collections::Generic::IEnumerable<Adapter^>
	{
		virtual System::Collections::IEnumerator^ GetEnumerator2() sealed = System::Collections::IEnumerable::GetEnumerator;

	internal:
		IDXGIFactory7* mDXGIFactory = nullptr;

	public:
		/// <summary>
		/// <see cref="Factory"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Factory();
		~Factory();
		!Factory();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> �������̽����� ���� ��.) ����� �÷��� ��ü�� �ݺ��ϴ� �����ڸ� ��ȯ�մϴ�.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<Adapter^>^ GetEnumerator();
	};
}