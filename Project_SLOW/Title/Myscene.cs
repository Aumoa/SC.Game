using System;
using SC.Game;

namespace Project_SLOW.Title
{
	class Myscene : Scene
	{
		bool start = false;
		Mypage mypage;

		public Myscene()
		{
			
		}

		public override void Update()
		{
			if ( start == false )
			{
				App.Navigate( mypage );

				start = true;
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			mypage = new Mypage();

			Add( CursorSystemGO.Instance );
		}

		public override void Unload()
		{

		}
	}
}
