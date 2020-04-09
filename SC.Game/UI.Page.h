#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// UI ��� ���̾ƿ��� ǥ���ϴ� �������� �����մϴ�.
	/// </summary>
	public ref class Page : public Element
	{
	protected:
		/// <summary>
		/// <see cref="Page"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü�� ���� �̸��� �����մϴ�. </param>
		Page( System::String^ xName );

	public:
		/// <summary>
		/// �������� �ܺο��� Ž���Ǿ��� �� ȣ��˴ϴ�.
		/// </summary>
		/// <param name="args"> ������ Ž�� �Ű������� ���޵˴ϴ�. </param>
		virtual void OnNavigatedTo( NavigationEventArgs^ args );

		/// <summary>
		/// �������� �ܺη� Ž���� �� ȣ��˴ϴ�.
		/// </summary>
		/// <param name="args"> ������ Ž�� �Ű������� ���޵˴ϴ�. </param>
		virtual void OnNavigatedFrom( NavigationEventArgs^ args );
	};
}