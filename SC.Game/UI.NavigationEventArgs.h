#pragma once

namespace SC::Game::UI
{
	ref class Page;

	/// <summary>
	/// Ž�� ��û�� ����� �� ���� Ž�� �Լ� �� �̺�Ʈ �ڵ鷯�� ���� �Ű������� �����մϴ�.
	/// </summary>
	public ref class NavigationEventArgs : public System::EventArgs
	{
		Page^ mPageFrom;
		Page^ mPageTo;

	public:
		/// <summary>
		/// <see cref="NavigationEventArgs"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pageFrom"> Ž�� ���� �������� �����մϴ�. </param>
		/// <param name="pageTo"> Ž�� ���� �������� �����մϴ�. </param>
		NavigationEventArgs( Page^ pageFrom, Page^ pageTo );

		/// <summary> Ž�� ���� �������� �����ɴϴ�. </summary>
		property Page^ PageFrom
		{
			Page^ get();
		}

		/// <summary> Ž�� ���� �������� �����ɴϴ�. </summary>
		property Page^ PageTo
		{
			Page^ get();
		}
	};
}