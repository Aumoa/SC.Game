#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ������ �ڻ��� ǥ���մϴ�.
	/// </summary>
	public ref class Asset
	{
		System::String^ mName;

	protected:
		/// <summary>
		/// <see cref="Asset"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> �ĺ��� �̸��� �����մϴ�. </param>
		Asset( System::String^ xName );

	public:
		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) ��ü�� ������ ������ �ؽ�Ʈ �������� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// �ĺ��� �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
	};
}