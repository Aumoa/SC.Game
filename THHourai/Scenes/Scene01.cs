using System;

using SC.Game;
using SC.Game.UI;

namespace THHourai.Scene01
{
	class Scene : SC.Game.Scene
	{
		Page page;
		bool isStart = false;

		public Scene()
		{

		}

		void Start()
		{
			App.Navigate( page );
		}

		public override void Update()
		{
			if ( !isStart )
			{
				Start();
				isStart = true;
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			var instance = GameCamera.Instance;

			Add( instance );

			var terrain = new Terrain( "Scene01.Terrain" );
			Add( terrain );

			page = new Page();
		}

		public override void Unload()
		{

		}
	}
}
