using System;
using System.Numerics;
using System.Drawing;
using SC.Game;

namespace PathFinder
{
	class Obstacle : GameObject
	{
		static Random random;
		static Mesh[] meshes;
		static PhysicsMaterial physicsMaterial;
		static Material killerMaterial;

		public Obstacle( ObstacleShape shape, ObstacleType type ) : this( shape, type, 0.1f + ( float )random.NextDouble() * 0.3f, 0.2f + ( float )random.NextDouble() * 1.0f )
		{

		}

		public Obstacle( ObstacleShape shape, ObstacleType type, float size, float height ) : this( shape, type, new Vector3( size, height, size ) )
		{

		}

		public Obstacle( ObstacleShape shape, ObstacleType type, Vector3 size ) : base( "PathFinder.Obstacle: " + type.ToString() )
		{
			AddComponent<MeshFilter>().Mesh = meshes[( int )shape];
			var mr = AddComponent<MeshRenderer>();
			var rigidbody = AddComponent<Rigidbody>();
			Transform.Scale = new Vector3( size.X, size.Y, size.Z );

			Collider col = null;

			switch ( shape )
			{
				case ObstacleShape.Cube:
					var bc = AddComponent<BoxCollider>();
					bc.HalfExtents = new Vector3( size.X, size.Y, size.Z );
					col = bc;
					break;
			}

			if ( col != null )
			{
				col.Material = physicsMaterial;
			}

			Type = type;

			switch ( type )
			{
				case ObstacleType.None:
					break;
				case ObstacleType.Killer:
					mr.Material = killerMaterial;
					break;
			}
		}

		static Obstacle()
		{
			random = new Random();
			meshes = new Mesh[( int )ObstacleShape.Count];

			meshes[0] = Mesh.CreateCube( "PathFinder.Obstacle.CubeType" );

			physicsMaterial = new PhysicsMaterial( "Obstacle.PhysicsMaterial" );
			physicsMaterial.StaticFriction = 0.1f;
			physicsMaterial.DynamicFriction = 0.1f;
			physicsMaterial.Restitution = 0.0f;

			killerMaterial = new Material( "Obstacle.killerMaterial" );
			killerMaterial.Color = Color.Red;
		}

		public ObstacleType Type
		{
			get;
			private set;
		}
	}
}