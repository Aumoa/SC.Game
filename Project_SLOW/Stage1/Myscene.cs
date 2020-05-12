using System;
using System.ComponentModel.Design;
using System.Drawing;
using System.Numerics;
using System.Security.Cryptography;
using SC.Game;
using SC.Game.Assets;

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

			Add( Boss.Instance );
			Add( GameCamera.Instance );
			Add( Terrain.Instance );
			Add( Sunlight.Instance );
			Add( CursorSystemGO.Instance );

			Boss.Instance.Transform.LocalPosition = new Vector3( 12.553f, 0.6376f, 5.93f );
			Boss.Instance.Transform.LocalRotation = Quaternion.CreateFromAxisAngle( Vector3.UnitY, ( float )Math.PI * -0.9f );

			var testPlayer = new Arisa( "testPlayer" );
			var basicClickEvent = testPlayer.AddComponent<BasicClickEvent>();
			basicClickEvent.Camera = GameCamera.Instance.GetComponentInChildren<Camera>();
			Add( testPlayer );

			var follow = GameCamera.Instance.AddComponent<CameraFollow>();
			follow.player = testPlayer;
		}

		public override void Unload()
		{

		}
	}
}
