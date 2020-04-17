using System;
using System.Numerics;
using SC.Game;

namespace THHourai.Scene01
{
	class Sunlight : GameObject
	{
		static Sunlight instance;

		Sunlight() : base( "Scene01.Sunlight" )
		{
			var light = AddComponent<Light>();
			light.Ambient = 0.2f;
			light.Diffuse = 0.8f;
			light.Specular = 1.5f;
			light.IsShadowCast = true;

			Transform.Position = new Vector3( -16.0f, 16.0f, -8.0f );
			Transform.LookAt( Vector3.Zero );
		}

		public static Sunlight Instance
		{
			get
			{
				if ( instance == null ) instance = new Sunlight();
				return instance;
			}
		}
	}
}