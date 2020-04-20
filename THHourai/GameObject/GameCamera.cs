using System;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	class GameCamera : GameObject
	{
		static GameCamera instance;

		GameCamera( string xName ) : base( xName )
		{
			var cam = new GameObject( xName + ".Camera" );
			cam.AddComponent<Camera>();
			var rotate = cam.AddComponent<CameraRotate>();
			cam.Transform.Parent = Transform;
			Cam = cam;

			var follow = AddComponent<CameraFollow>();
			rotate.target = follow;

			WASDMove.cam = follow;
		}

		public GameObject Cam
		{
			get;
			private set;
		}

		public static GameCamera Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new GameCamera( "Scene00.GameCamera.Instance" );
				}

				return instance;
			}
		}
	}
}