#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// �ý��ۿ� �����ϴ� ���� ����� �Ǵ� ����Ʈ���� ���� ����Ϳ� ���� ����� �����մϴ�.
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
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) ���÷����� ������ ��ȸ�Ͽ� ��ü�� �ؽ�Ʈ ������ �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> �������̽����� ���� ��.) ��� ���÷��� �÷��� ��ü�� �ݺ��ϴ� �����ڸ� ��ȯ�մϴ�.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<Output^>^ GetEnumerator();

		/// <summary>
		/// ����� ������ ��ȸ�մϴ�.
		/// </summary>
		AdapterInfo QueryInfo();
	};
}