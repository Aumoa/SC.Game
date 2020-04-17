using System;
using System.Numerics;
using SC.Game;

namespace PathFinder
{
	class MainCamera : GameObject
	{
		static MainCamera instance;
		static Texture2D skyboxTexture;

		MainCamera() : base( "MainCamera" )
		{
			var go = new GameObject( "cam" );
			var cam = go.AddComponent<Camera>();
			go.Transform.LocalPosition = new Vector3( 0, 10.0f, -2.0f );
			go.Transform.LocalLookAt( Vector3.Zero );
			go.Transform.Parent = Transform;

			skyboxTexture = new Texture2D( "MainCamera.skyboxTexture", @"Assets\Textures\DaylightSkybox.png", TextureFormat.PRGBA_32bpp );
			cam.Skybox = skyboxTexture;

			AddComponent<CamChaser>();
		}

		public static MainCamera Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new MainCamera();
				}

				return instance;
			}
		}
	}
}