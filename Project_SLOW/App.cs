using System;
using SC.Game;

namespace Project_SLOW
{
	delegate void DisposingDelegate();

	class App : Application
	{
		public App() : base( new AppConfiguration { AppName = "Project:Slow" } )
		{

		}

		public override void OnStart()
		{
			var title = SceneManager.LoadScene<Title.Myscene>();
			SceneManager.Start( title );
		}

		public override int OnExit()
		{
			Disposing?.Invoke();

			// 모든 세대의 데이터를 수집합니다.
			GC.Collect();

			return 0;
		}

		public override void OnActive( bool activated )
		{
			if ( activated )
			{
				Cursor.LockState = CursorLockMode.Confined;
				Activated = true;
			}
			else
			{
				Cursor.LockState = CursorLockMode.None;
				Activated = false;
			}
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

		public static bool Activated
		{
			get;
			private set;
		}
	}
}
