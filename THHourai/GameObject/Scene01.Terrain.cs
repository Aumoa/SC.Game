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
			var plane = new GameObject( xName + ":plane" );
			plane.AddComponent<MeshFilter>().Mesh = Mesh.CreatePlane( xName + ".MeshPlane" );
			plane.AddComponent<MeshRenderer>().Material = material;
			plane.AddComponent<BoxCollider>().Center = new Vector3( 0.0f, -1.0f, 0.0f );

			plane.Transform.Scale = new Vector3( 10.0f, 1.0f, 10.0f );
			plane.Transform.Parent = Transform;

			LoadTrees();

			plane.Tag = ( Tag )( CustomTag.CameraBlocker | CustomTag.Terrain );
		}

		static Terrain()
		{
			material = new Material( "Terrain.material" );

			material.DiffuseMap = new Texture2D( "Terrain.material.diffuseMap", @"Assets\Texture\templeBase01_diffuse.jpg", TextureFormat.PRGBA_32bpp );
			material.NormalMap = new Texture2D( "Terrain.material.diffuseMap", @"Assets\Texture\templeBase01_normal.jpg", TextureFormat.PRGBA_32bpp );
			material.Transform = Matrix3x2.CreateScale( 10.0f );
		}

		void LoadTrees()
		{
			var tree0 = new AshenTree( "Scene01.Terrain.tree0" );
			tree0.Transform.Parent = Transform;
			tree0.Transform.Scale = new Vector3( 0.01f, 0.01f, 0.01f );
		}
	}
}