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
	internal:
		static System::UInt32 mWidth;
		static System::UInt32 mHeight;

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
		/// ���� Ȱ��ȭ�ǰų� ��Ȱ��ȭ�� �� ȣ��˴ϴ�.
		/// </summary>
		/// <param name="activated"> ���� Ȱ��ȭ ���¸� ��Ÿ���ϴ�. </param>
		virtual void OnActive( bool activated );

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
		/// �ۿ� ���� �̺�Ʈ�� �߻���ŵ�ϴ�.
		/// </summary>
		/// <param name="exitCode"> ���� �ڵ带 �����մϴ�. </param>
		static void Quit( int exitCode );

		/// <summary>
		/// ���� ������ �����ɴϴ�.
		/// </summary>
		property AppConfiguration Configuration { AppConfiguration get(); }

		/// <summary>
		/// ���� �� ȭ���� �ʺ� �����ɴϴ�.
		/// </summary>
		static property System::UInt32 Width
		{
			System::UInt32 get();
			void set( System::UInt32 value );
		}

		/// <summary>
		/// ���� �� ȭ���� ���̸� �����ɴϴ�.
		/// </summary>
		static property System::UInt32 Height
		{
			System::UInt32 get();
			void set( System::UInt32 value );
		}
	};

	ref class ApplicationCore abstract
	{
	public:
		static Application^ mApp;
		static AppConfiguration mConfiguration;
		static UI::Page^ mPage;
	};
}