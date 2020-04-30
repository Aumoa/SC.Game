using System;
using System.Numerics;
using System.Threading.Tasks;

using SC.Game;
using SC.Game.UI;

namespace THHourai.Scene01
{
	class Scene : SC.Game.Scene
	{
		Page page;
		bool isStart = false;
		Task<GameObject> mokou;

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

			if ( mokou != null && mokou.IsCompleted )
			{
				var go = mokou.Result;
				mokou = null;
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			var instance = GameCamera.Instance;
			var terrain = new Terrain( "Scene01.Terrain" );

			Add( instance );
			Add( terrain );
			Add( Sunlight.Instance );
			Add( GamePlayer.Instance );

			var sf = Sunlight.Instance.AddComponent<ShadowFollow>();
			sf.Target = instance.Transform;

			page = new Page();
		}

		public override void Unload()
		{

		}
	}
}
