using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;
using SC.Game.Assets;

namespace Project_SLOW.Stage1
{
	class Terrain : SingletonGameObject<Terrain>
	{
		static Material material;
		static Mesh mesh;

		static LoadedInfo platform;

		static Texture2D platform_texture;

		public Terrain() : base( "Terrain" )
		{
			InitializeAssets();
			InitializeGameObjects();

			var plane = new GameObject( "plane" );
			plane.Transform.Scale = new Vector3( 1000.0f, 1.0f, 1000.0f );
			plane.AddComponent<MeshFilter>().Mesh = mesh;
			plane.AddComponent<MeshRenderer>().Material = material;
			plane.Transform.Parent = Transform;
			var boxCol = plane.AddComponent<BoxCollider>();
			boxCol.Center = new Vector3( 0.0f, -1.0f, 0.0f );

			Tag = ( Tag )CustomTag.Terrain;
		}

		void InitializeAssets()
		{
			mesh = Mesh.CreatePlane( "BasicField.Terrain.mesh" );
			material = new Material( "BasicField.Terrain.material" );
			material.DiffuseMap = new Texture2D( "grass01", "Assets/Texture/grass/grass01.jpg", TextureFormat.PRGBA_32bpp );
			material.NormalMap = new Texture2D( "grass01_n", "Assets/Texture/grass/grass01_n.jpg", TextureFormat.PRGBA_32bpp );
			material.Transform = Matrix3x2.CreateScale( 500.0f );

			platform = AssetBundle.LoadAsset( @"Assets\Model\Altar_Ruins_FREE\Platform.fbx" );
			platform_texture = new Texture2D( "Platform_diffuse.png", @"Assets\Model\Altar_Ruins_FREE\Textures\Platform\Platform_diffuse.png", TextureFormat.PRGBA_32bpp );
		}

		void InitializeGameObjects()
		{
			var platform = Terrain.platform.Composed.Clone() as GameObject;
			platform.Transform.LocalPosition = new Vector3( 10.0f, 0.0f, 5.0f );
			platform.Transform.LocalScale = new Vector3( -1.0f, 1.0f, 1.0f );
			platform.Transform.Parent = Transform;
			var mesh = platform.GetChild( 0 ).GetChild( 0 ).GetChild( 0 );
			mesh.AddComponent<MeshCollider>();
			mesh.GetComponent<MeshRenderer>().Material.DiffuseMap = platform_texture;

			var unit = new GameObject( "unit" );
			unit.AddComponent<MeshFilter>().Mesh = Mesh.CreateCube( "cube unit" );
			unit.AddComponent<MeshRenderer>();
			unit.Transform.Parent = Transform;
		}
	}
}
