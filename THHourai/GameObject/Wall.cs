using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	class Wall : GameObject
	{
		static Mesh cube;
		static PhysicsMaterial physicsMaterial;

		public Wall( string xName ) : base( xName )
		{
			AddComponent<MeshFilter>().Mesh = cube;
			AddComponent<MeshRenderer>();
			AddComponent<BoxCollider>();

			Tag = Tag | ( Tag )CustomTag.CameraBlocker;
		}

		static Wall()
		{
			cube = Mesh.CreateCube( "THHourai.Wall.cube" );
			physicsMaterial = new PhysicsMaterial( "THHourai.Wall.physicsMaterial" );
			physicsMaterial.Restitution = 0.0f;
		}
	}
}
