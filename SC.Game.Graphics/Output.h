#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// ����Ϳ� ����� ���÷��̿� ���� ���� ����� �����մϴ�.
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
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) ���÷����� ������ ��ȸ�Ͽ� ��ü�� �ؽ�Ʈ ������ �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// ���� ���÷��� ������ ��ȸ�մϴ�.
		/// </summary>
		OutputQueryInfo QueryInfo();
	};
}