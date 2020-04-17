using System;
using System.Numerics;
using System.Drawing;
using SC.Game;

namespace PathFinder
{
	class Terrain : GameObject
	{
		static Terrain instance;
		static Material material;
		static Material goalMaterial;
		static PhysicsMaterial physicsMaterial;

		static Mesh mesh;

		Terrain() : base( "Scene01.Terrain" )
		{
			mesh = Mesh.CreateCube( "Scene01.Terrain.cube" );
			material = new Material( "Scene01.Terrain.material" );
			material.Color = Color.LightYellow;
			goalMaterial = new Material( "Scene01.Terrain.goalMaterial" );
			goalMaterial.Color = Color.LightGreen;
			physicsMaterial = new PhysicsMaterial( "Terrain.PhysicsMaterial" );
			physicsMaterial.StaticFriction = 1.5f;
			physicsMaterial.DynamicFriction = 1.5f;
			physicsMaterial.Restitution = 0.0f;

			GameObject go = new GameObject( "Scene01.Terrain.plane" );
			go.AddComponent<MeshFilter>().Mesh = mesh;
			go.AddComponent<MeshRenderer>().Material = material;
			var boxCol = go.AddComponent<BoxCollider>();
			go.Transform.LocalScale = new Vector3( 4.0f, 1.0f, 7.0f );
			go.Transform.LocalPosition = new Vector3( 0.0f, -1.0f, 7.0f );
			boxCol.HalfExtents = new Vector3( 4.0f, 1.0f, 7.0f );
			boxCol.Material = physicsMaterial;
			go.Transform.Parent = Transform;

			go = new GameObject( "Scene01.Terrain.goal" );
			go.AddComponent<MeshFilter>().Mesh = mesh;
			go.AddComponent<MeshRenderer>().Material = goalMaterial;
			boxCol = go.AddComponent<BoxCollider>();

			go.Transform.Position = new Vector3( 0.0f, -1.0f, 14.5f );
			go.Transform.Scale = new Vector3( 4.0f, 1.0f, 0.5f );
			go.Transform.Parent = Transform;

			boxCol.IsTrigger = true;
			boxCol.Center = new Vector3( 0.0f, 2.0f, 0.0f );
			boxCol.HalfExtents = new Vector3( 4.0f, 1.0f, 0.5f );
			boxCol.Material = physicsMaterial;
		}

		public static Terrain Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new Terrain();
				}

				return instance;
			}
		}
	}
}