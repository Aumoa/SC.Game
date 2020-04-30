using System;
using System.Numerics;
using SC.Game;

namespace Project_SLOW.Stage1
{
	class GameCamera : SingletonGameObject<GameCamera>
	{
		GameObject cameraObject;

		public GameCamera() : base( "GameCamera" )
		{
			cameraObject = new GameObject( "cameraObject" );
			cameraObject.AddComponent<Camera>();
			cameraObject.AddComponent<CameraAction>();
			cameraObject.Transform.Parent = Transform;

			AddComponent<CameraMove>();
		}
	}
}