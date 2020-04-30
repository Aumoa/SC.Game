using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace Shinsekai.BasicField
{
	class Scene : SC.Game.Scene
	{
		bool start = false;
		BaseCombatPage page;

		public Scene() : base()
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
			Add( Terrain.Instance );
			Add( GameCamera.Instance );
			Add( Sunlight.Instance );

			var mokou = new Mokou( "testPlayer" );
			Add( mokou );
			mokou.AddComponent<GaugeLinker>();

			Player.playable = mokou;
			mokou.AddComponent<ClickEvent>();

			var enemy = new Mokou( "testEnemy" );
			Field.enemys.Add( enemy );
			enemy.Transform.LocalPosition = new Vector3( 5.0f, 0.0f, 0.0f );
			enemy.AddComponent<EnemyGaugeLinker>();
			Add( enemy );

			page = new BaseCombatPage();

			var block = new GameObject( "block" );
			block.AddComponent<MeshFilter>().Mesh = Mesh.CreateCube( "block.cube" );
			block.AddComponent<MeshRenderer>();
			block.AddComponent<BoxCollider>();
			block.Transform.LocalPosition = new Vector3( -4.0f, 1.0f, 0.0f );
			Add( block );
		}

		public override void Unload()
		{

		}
	}
}
