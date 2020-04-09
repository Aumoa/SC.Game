#pragma once

#include "AppConfiguration.h"

namespace SC::Game::UI
{
	ref class Page;
}

namespace SC::Game
{
	/// <summary>
	/// 게임 앱에 대한 제어 함수를 제공하며 앱의 기초 처리기에 대한 인터페이스를 제공합니다.
	/// </summary>
	public ref class Application abstract
	{
	public:
		/// <summary>
		/// <see cref="Application"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="configuration"> 앱 설정을 전달합니다. </param>
		Application( AppConfiguration configuration );

		/// <summary>
		/// 앱이 시작될 때 호출됩니다.
		/// </summary>
		virtual void OnStart() = 0;

		/// <summary>
		/// 앱이 종료될 때 호출됩니다. 앱은 종료 코드를 반환해야 합니다. 
		/// </summary>
		virtual int OnExit() = 0;

		/// <summary>
		/// 응용 프로그램의 진입점에 의해 앱을 실행합니다. 이 함수는 앱이 종료될 때까지 반환하지 않습니다.
		/// </summary>
		/// <param name="app"> 게임 앱 개체를 전달합니다. </param>
		static int Start( Application^ app );

		/// <summary>
		/// 앱의 UI 레이아웃을 지정된 페이지로 이동합니다.
		/// </summary>
		static void Navigate( UI::Page^ page );

		/// <summary>
		/// 앱의 설정을 가져옵니다.
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