using System;
using SC.Game;

namespace THHourai.Scene01
{
	class Cube : GameObject
	{
		static Mesh cube;
		static PhysicsMaterial physicsMaterial;

		public Cube( string xName ) : base( xName )
		{
			AddComponent<MeshFilter>().Mesh = cube;
			AddComponent<MeshRenderer>();
			AddComponent<Rigidbody>();
			var collider = AddComponent<BoxCollider>();
			collider.Material = physicsMaterial;
		}

		static Cube()
		{
			if ( cube == null )
			{
				cube = Mesh.CreateCube( "Scene01.Cube.cube" );
				physicsMaterial = new PhysicsMaterial( "Scene01.Cube.physicsMaterial" );
				physicsMaterial.Restitution = 0.01f;
			}
		}
	}
}