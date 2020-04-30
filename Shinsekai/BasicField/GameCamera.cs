using System;
using System.Numerics;
using SC.Game;

namespace Shinsekai.BasicField
{
	class GameCamera : SingletonGO<GameCamera>
	{
		GameObject cameraObject;

		public GameCamera() : base( "BasicField.GameCamera" )
		{
			cameraObject = new GameObject( "BasicField.GameCamera.cameraObject" );
			cameraObject.AddComponent<Camera>();
			cameraObject.AddComponent<CameraAction>();
			cameraObject.Transform.Parent = Transform;

			AddComponent<CameraMove>();
			//AddComponent<ClickMove>();
		}
	}
}