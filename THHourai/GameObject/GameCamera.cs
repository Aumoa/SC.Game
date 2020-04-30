using System;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	class GameCamera : GameObject
	{
		static GameCamera instance;

		GameObject cameraObject;

		GameCamera( string xName ) : base( xName )
		{
			cameraObject = new GameObject( xName + ".cameraObject" );
			cameraObject.AddComponent<Camera>();
			cameraObject.AddComponent<CameraAction>();
			cameraObject.Transform.Parent = Transform;

			AddComponent<CameraMove>();
			AddComponent<ClickMove>();
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