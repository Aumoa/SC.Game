#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ���� ���븦 ǥ���մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Bone sealed : public Component
	{
		System::String^ mName;
		int mIndex = 0;

	public:
		/// <summary>
		/// <see cref="Bone"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Bone();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// ������ �̸��� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
			void set( System::String^ value );
		}

		/// <summary>
		/// ������ ���� ��ȣ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property int Index
		{
			int get();
			void set( int value );
		}
	};
}