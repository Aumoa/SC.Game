using System;
using System.Numerics;
using SC.Game;

namespace THHourai.Scene01
{
	class Sunlight : SingletonGameObject<Sunlight>
	{
		public Sunlight() : base( "Scene01.Sunlight" )
		{
			var light = AddComponent<Light>();
			light.Ambient = 0.2f;
			light.Diffuse = 0.8f;
			light.Specular = 1.5f;
			light.IsShadowCast = true;
			light.Width = 60.0f;
			light.Height = 60.0f;

			Transform.Position = new Vector3( -8.0f, 16.0f, -4.0f );
			Transform.LookAt( Vector3.Zero );
		}
	}
}