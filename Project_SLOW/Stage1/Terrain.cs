using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace Project_SLOW.Stage1
{
	class Terrain : SingletonGameObject<Terrain>
	{
		static Material material;
		static Mesh mesh;

		public Terrain() : base( "Terrain" )
		{
			InitializeAssets();
			InitializeComponents();

			Transform.Scale = new Vector3( 1000.0f, 1.0f, 1000.0f );
			Tag = ( Tag )CustomTag.Terrain;
		}

		void InitializeAssets()
		{
			mesh = Mesh.CreatePlane( "BasicField.Terrain.mesh" );
			material = new Material( "BasicField.Terrain.material" );
			material.DiffuseMap = new Texture2D( "grass01", "Assets/Texture/grass/grass01.jpg", TextureFormat.PRGBA_32bpp );
			material.NormalMap = new Texture2D( "grass01_n", "Assets/Texture/grass/grass01_n.jpg", TextureFormat.PRGBA_32bpp );
			material.Transform = Matrix3x2.CreateScale( 500.0f );
		}

		void InitializeComponents()
		{
			AddComponent<MeshFilter>().Mesh = mesh;
			AddComponent<MeshRenderer>().Material = material;
			var boxCol = AddComponent<BoxCollider>();
			boxCol.Center = new Vector3( 0.0f, -1.0f, 0.0f );
		}
	}
}
