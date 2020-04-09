using System;
using SC.Game;

namespace THHourai
{
	delegate void DisposingDelegate();

	class App : Application
	{
		public App() : base( new AppConfiguration { AppName = "Touhou Hourai Story" } )
		{

		}

		public override void OnStart()
		{
			var demoScene = SceneManager.LoadScene<DemoScene>();
			SceneManager.Start( demoScene );
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