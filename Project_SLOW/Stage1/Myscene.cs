using System;
using SC.Game;

namespace Project_SLOW.Stage1
{
	class Myscene : Scene
	{
		bool start = false;
		Mypage page;

		public Myscene() : base()
		{

		}

		public override void Update()
		{
			if ( !start )
			{
				App.Navigate( page );

				start = true;
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			page = new Mypage();

			Add( GameCamera.Instance );
			Add( Terrain.Instance );
			Add( Sunlight.Instance );
			Add( CursorSystemGO.Instance );

			var testPlayer = new Mokou( "testPlayer" );
			var basicClickEvent = testPlayer.AddComponent<BasicClickEvent>();
			basicClickEvent.Camera = GameCamera.Instance.GetComponentInChildren<Camera>();
			Add( testPlayer );
		}

		public override void Unload()
		{

		}
	}
}
