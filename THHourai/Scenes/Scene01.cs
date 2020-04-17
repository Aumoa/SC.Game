using System;
using System.Numerics;

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
			var terrain = new Terrain( "Scene01.Terrain" );
			Cube[] cubes = new Cube[10];

			for ( int i = 0; i < 10; ++i )
			{
				cubes[i] = new Cube( string.Format( "Scene01.cubes[{0}]", i ) );
				cubes[i].Transform.Position = new Vector3( 0 + i * 2.0f, 1.0f, 0.0f );
				cubes[i].AddComponent<Rigidbody>();
				cubes[i].AddComponent<BoxCollider>();
				Add( cubes[i] );
			}

			var boxCol = terrain.AddComponent<BoxCollider>();
			boxCol.Center = new Vector3( 0, -1.0f, 0 );
			boxCol.HalfExtents = new Vector3( 100.0f, 1.0f, 100.0f );

			cubes[0].AddComponent<WASDMove>();

			Add( instance );
			Add( terrain );
			Add( Sunlight.Instance );

			var sf = Sunlight.Instance.AddComponent<ShadowFollow>();
			sf.Target = instance.Transform;

			page = new Page();
		}

		public override void Unload()
		{

		}
	}
}
