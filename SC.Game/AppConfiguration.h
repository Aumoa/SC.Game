#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� �� ȯ�� ������ ǥ���մϴ�.
	/// </summary>
	public value struct AppConfiguration
	{
	internal:
		System::String^ mAdapterName;

	public:
		/// <summary>
		/// ���� �̸��� �����ϰų� �����ɴϴ�.
		/// </summary>
		System::String^ AppName;

		/// <summary>
		/// �ʴ� ���� ���� Ƚ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		int PhysicsUpdatesPerSecond;

		/// <summary>
		/// ���� ���� ����ȭ ��� Ȱ��ȭ ���¸� ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		bool VSync;

	public:
		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) ���� ��ü�� �ؽ�Ʈ ǥ���� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// �ý��ۿ��� ����ϴ� �׷��� ������� ������ ������ �����ɴϴ�.
		/// </summary>
		property System::String^ AdapterName
		{
			System::String^ get();
		}
	};
}