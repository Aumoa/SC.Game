using System;
using System.Drawing;
using System.Numerics;
using SC.Game;

namespace PathFinder
{
	class Sunlight : GameObject
	{
		static Sunlight instance;

		Sunlight() : base( "sunlight" )
		{
			var light = AddComponent<Light>();
			light.Color = Color.White;
			light.Ambient = 0.2f;
			light.Diffuse = 0.8f;
			light.Specular = 0.0f;
			light.IsShadowCast = true;
			Transform.Position = new Vector3( -5.0f, 10.0f, -5.0f );
			Transform.LookAt( Vector3.Zero );
		}

		public static Sunlight Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new Sunlight();
				}

				return instance;
			}
		}
	}
}