using System;
using System.Numerics;
using SC.Game;

namespace PathFinder
{
	class PlayerSphere : GameObject
	{
		static PlayerSphere instance;
		static Mesh sphere;
		static PhysicsMaterial physicsMaterial;

		PlayerSphere() : base( "player" )
		{
			sphere = Mesh.CreateGeosphere( "player.sphere", 4 );
			AddComponent<MeshFilter>().Mesh = sphere;
			AddComponent<MeshRenderer>();
			var rigidbody = AddComponent<Rigidbody>();
			var wasd = AddComponent<WASDWalk>();
			var sc = AddComponent<SphereCollider>();

			Transform.Scale = new Vector3( 0.5f, 0.5f, 0.5f );
			sc.Radius = 0.5f;
			rigidbody.IsKinematic = true;

			var pos = Transform.Position;
			pos.Y = Transform.Scale.Y;
			Transform.Position = pos;

			physicsMaterial = new PhysicsMaterial( "PlayerSphere.PhysicsMaterial" );
			physicsMaterial.StaticFriction = 1.5f;
			physicsMaterial.DynamicFriction = 1.5f;
			physicsMaterial.Restitution = 0.0f;
			sc.Material = physicsMaterial;
		}

		public static PlayerSphere Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new PlayerSphere();
				}
				return instance;
			}
		}
	}
}