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

			plane.Tag = ( Tag )CustomTag.CameraBlocker;

			var wallLeft = new Wall( xName + ":wallLeft" );
			wallLeft.Transform.LocalPosition = new Vector3( -9.5f, 3.0f, 0.0f );
			wallLeft.Transform.LocalScale = new Vector3( 0.5f, 3.0f, 10.0f );
			wallLeft.Transform.Parent = Transform;

			var wallRight = new Wall( xName + ":wallRight" );
			wallRight.Transform.LocalPosition = new Vector3( 9.5f, 3.0f, 0.0f );
			wallRight.Transform.LocalScale = new Vector3( 0.5f, 3.0f, 10.0f );
			wallRight.Transform.Parent = Transform;

			var wallFar = new Wall( xName + ":wallFar" );
			wallFar.Transform.LocalPosition = new Vector3( 0.0f, 3.0f, 9.5f );
			wallFar.Transform.LocalScale = new Vector3( 10.0f, 3.0f, 0.5f );
			wallFar.Transform.Parent = Transform;

			var wallNear = new Wall( xName + ":wallNear" );
			wallNear.Transform.LocalPosition = new Vector3( 0.0f, 3.0f, -9.5f );
			wallNear.Transform.LocalScale = new Vector3( 10.0f, 3.0f, 0.5f );
			wallNear.Transform.Parent = Transform;
		}

		static Terrain()
		{
			material = new Material( "Terrain.material" );

			material.DiffuseMap = new Texture2D( "Terrain.material.diffuseMap", @"Assets\Texture\templeBase01_diffuse.jpg", TextureFormat.PRGBA_32bpp );
			material.NormalMap = new Texture2D( "Terrain.material.diffuseMap", @"Assets\Texture\templeBase01_normal.jpg", TextureFormat.PRGBA_32bpp );
			material.Transform = Matrix3x2.CreateScale( 10.0f );
		}
	}
}