using System;
using System.Numerics;
using SC.Game;

namespace Project_SLOW.Stage1
{
	class Sunlight : SingletonGameObject<Sunlight>
	{
		public Sunlight() : base( "Sunlight" )
		{
			InitializeComponents();
		}

		void InitializeComponents()
		{
			var light = AddComponent<Light>();
			light.Ambient = 0.2f;
			light.Diffuse = 0.8f;
			light.Specular = 1.5f;
			light.IsShadowCast = true;
			light.Width = 60.0f;
			light.Height = 60.0f;

			Transform.Position = new Vector3( 3.0f, 10.0f, 5.0f );
			Transform.LookAt( Vector3.Zero );
		}
	}
}
