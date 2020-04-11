using System;
using SC.Game;

namespace THHourai.Scene01
{
	class Terrain : GameObject
	{
		public Terrain( string xName ) : base( xName )
		{
			AddComponent<MeshFilter>().Mesh = Mesh.CreatePlane( xName + ".MeshPlane" );
			AddComponent<MeshRenderer>();
		}
	}
}