using System;
using System.ComponentModel;
using SC.Game;

namespace Shinsekai
{
	class App : Application
	{
		static App instance;

		public App() : base( Config )
		{

		}

		static void Main( string[] args )
		{
			Start( Instance );
		}

		public override void OnStart()
		{
			var scene = SceneManager.LoadScene<BasicField.Scene>();
			SceneManager.Start( scene );
		}

		public override void OnActive( bool activated )
		{
			if ( activated )
			{
				Cursor.LockState = CursorLockMode.Confined;
			}
			else
			{
				Cursor.LockState = CursorLockMode.None;
			}
		}

		public override int OnExit()
		{
			if ( Cursor.LockState == CursorLockMode.Confined )
			{
				Cursor.LockState = CursorLockMode.None;
			}

			return 0;
		}

		static AppConfiguration Config
		{
			get
			{
				return new AppConfiguration
				{
					AppName = "Project: Shinsekai",
					PhysicsUpdatesPerSecond = 60
				};
			}
		}

		public static App Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new App();
				}

				return instance;
			}
		}
	}
}
