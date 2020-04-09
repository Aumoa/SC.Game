#pragma once

#include "AppConfiguration.h"

namespace SC::Game::UI
{
	ref class Page;
}

namespace SC::Game
{
	/// <summary>
	/// ���� �ۿ� ���� ���� �Լ��� �����ϸ� ���� ���� ó���⿡ ���� �������̽��� �����մϴ�.
	/// </summary>
	public ref class Application abstract
	{
	public:
		/// <summary>
		/// <see cref="Application"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="configuration"> �� ������ �����մϴ�. </param>
		Application( AppConfiguration configuration );

		/// <summary>
		/// ���� ���۵� �� ȣ��˴ϴ�.
		/// </summary>
		virtual void OnStart() = 0;

		/// <summary>
		/// ���� ����� �� ȣ��˴ϴ�. ���� ���� �ڵ带 ��ȯ�ؾ� �մϴ�. 
		/// </summary>
		virtual int OnExit() = 0;

		/// <summary>
		/// ���� ���α׷��� �������� ���� ���� �����մϴ�. �� �Լ��� ���� ����� ������ ��ȯ���� �ʽ��ϴ�.
		/// </summary>
		/// <param name="app"> ���� �� ��ü�� �����մϴ�. </param>
		static int Start( Application^ app );

		/// <summary>
		/// ���� UI ���̾ƿ��� ������ �������� �̵��մϴ�.
		/// </summary>
		static void Navigate( UI::Page^ page );

		/// <summary>
		/// ���� ������ �����ɴϴ�.
		/// </summary>
		property AppConfiguration Configuration { AppConfiguration get(); }
	};

	ref class ApplicationCore abstract
	{
	public:
		static Application^ mApp;
		static AppConfiguration mConfiguration;
		static UI::Page^ mPage;
	};
}