using System;
using SC.Game;

namespace THHourai.Scene01
{
	class Cube : GameObject
	{
		static Mesh cube;

		public Cube( string xName ) : base( xName )
		{
			AddComponent<MeshFilter>().Mesh = cube;
			AddComponent<MeshRenderer>();
		}

		static Cube()
		{
			if ( cube == null )
			{
				cube = Mesh.CreateCube( "Scene01.Cube.cube" );
			}
		}
	}
}