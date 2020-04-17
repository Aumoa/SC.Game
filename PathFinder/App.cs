using System;
using SC.Game;

namespace PathFinder
{
	delegate void DisposingDelegate();

	class App : Application
	{
		public App() : base( new AppConfiguration { AppName = "PathFinder" } )
		{

		}

		public override void OnStart()
		{
			// 시작 장면을 불러오고 즉시 시작합니다.
			SceneManager.Start( SceneManager.LoadScene<Scene01.Scene>() );
		}

		public override int OnExit()
		{
			Disposing?.Invoke();

			// 모든 세대의 데이터를 수집합니다.
			GC.Collect();

			return 0;
		}

		static void Main()
		{
			Start( Instance = new App() );
		}

		public static App Instance
		{
			get;
			private set;
		}

		public static event DisposingDelegate Disposing;
	}
}