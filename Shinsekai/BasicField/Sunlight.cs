using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace Shinsekai.BasicField
{
	class Sunlight : SingletonGO<Sunlight>
	{
		public Sunlight() : base( "BasicField.Sunlight" )
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
