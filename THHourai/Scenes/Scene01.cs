﻿using System;
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
			Cube[] cubes = new Cube[10];

			for ( int i = 0; i < 5; ++i )
			{
				cubes[i] = new Cube( string.Format( "Scene01.cubes[{0}]", i ) );
				cubes[i].Transform.Position = new Vector3( 2.0f + i * 2.0f, 1.0f, 0.0f );
				Add( cubes[i] );
			}

			Add( instance );
			Add( terrain );
			Add( Sunlight.Instance );
			Add( GamePlayer.Instance );

			var sf = Sunlight.Instance.AddComponent<ShadowFollow>();
			sf.Target = instance.Transform;

			page = new Page();

			GameCamera.Instance.GetComponent<CameraFollow>().target = GamePlayer.Instance.Transform;
		}

		public override void Unload()
		{

		}
	}
}
