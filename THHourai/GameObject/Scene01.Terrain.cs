using System;
using System.Numerics;
using SC.Game;

namespace THHourai.Scene01
{
	class Terrain : GameObject
	{
		static Material material;

		public Terrain( string xName ) : base( xName )
		{
			AddComponent<MeshFilter>().Mesh = Mesh.CreatePlane( xName + ".MeshPlane" );
			AddComponent<MeshRenderer>().Material = material;
			Transform.Scale = new Vector3( 100.0f, 1.0f, 100.0f );
			Transform.LocalPosition = new Vector3( 90.0f, 0.0f, 90.0f );
		}

		static Terrain()
		{
			material = new Material( "Terrain.material" );

			material.DiffuseMap = new Texture2D( "Terrain.material.diffuseMap", @"Assets\Texture\templeBase01_diffuse.jpg", TextureFormat.PRGBA_32bpp );
			material.NormalMap = new Texture2D( "Terrain.material.diffuseMap", @"Assets\Texture\templeBase01_normal.jpg", TextureFormat.PRGBA_32bpp );
			material.Transform = Matrix3x2.CreateScale( 100.0f );
		}
	}
}