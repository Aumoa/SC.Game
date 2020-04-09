#pragma once

namespace SC::Game
{
	/// <summary>
	/// ��鿡 ���Ե� �� �ִ�, ���� ���迡�� ǥ���Ǵ� ��� ��ü�� ���� �������̽��� �����մϴ�.
	/// </summary>
	public ref class GameObject
	{
		System::String^ mName;

	public:
		/// <summary>
		/// <see cref="GameObject"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü�� �ĺ� �̸��� �����մϴ�. </param>
		GameObject( System::String^ xName );

		/// <summary>
		/// ��ü�� �ĺ� �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}
	};
}