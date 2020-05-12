using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.SqlServer.Server;
using System.IO;
using Assimp;

using SDK = Assimp;
using Assimp.Unmanaged;

namespace SC.Game.Assets.Assimp
{
	partial class Parser
	{
		void ProcessMaterials()
		{
			materials = new Material[scene.MaterialCount];

			for ( int i = 0; i < materials.Length; ++i )
			{
				var aiMat = scene.Materials[i];
				var mat = new Material( string.Format( "{0}:{1}", filename, aiMat.Name ) );

				if ( aiMat.GetMaterialTextureCount( TextureType.Diffuse ) > 0 )
				{
					TextureSlot slot;
					aiMat.GetMaterialTexture( TextureType.Diffuse, 0, out slot );

					string[] path = slot.FilePath.Split( '*' );

					if ( string.IsNullOrWhiteSpace( path[0] ) )
					{
						int embeded_index = int.Parse( path[1] );
						var texture = scene.Textures[embeded_index];

						var assetName = string.Format( "{0}:{1}_embeded{2}", filename, aiMat.Name, embeded_index );
						var texture0 = new Texture2D( assetName, texture.CompressedData, ( uint )texture.CompressedDataSize, TextureFormat.PRGBA_32bpp );

						mat.DiffuseMap = texture0;
						textures.Add( texture0 );
					}
					else
					{
						try
						{
							var texture0 = new Texture2D( string.Format( "{0}:{1}:DIFFUSE0", filename, aiMat.Name ), Path.Combine( directory, path[0] ), TextureFormat.PRGBA_32bpp );
							mat.DiffuseMap = texture0;
							textures.Add( texture0 );

							if ( path.Length != 1 && !string.IsNullOrWhiteSpace( path[1] ) )
							{
								var texture1 = new Texture2D( string.Format( "{0}:{1}:DIFFUSE1", filename, aiMat.Name ), Path.Combine( directory, path[1] ), TextureFormat.PRGBA_32bpp );
								mat.DiffuseLayerMap = texture1;
								textures.Add( texture1 );
							}
						}
						catch ( FileNotFoundException )
						{

						}
					}
				}

				if ( aiMat.GetMaterialTextureCount( TextureType.Normals ) > 0 )
				{
					TextureSlot slot;
					aiMat.GetMaterialTexture( TextureType.Normals, 0, out slot );

					if ( slot.FilePath[0] == '*' )
					{
						int embeded_index = int.Parse( slot.FilePath.Substring( 1 ) );
						var texture = scene.Textures[embeded_index];

						var assetName = string.Format( "{0}:{1}_embeded{2}", filename, aiMat.Name, embeded_index );
						var texture0 = new Texture2D( assetName, texture.CompressedData, ( uint )texture.CompressedDataSize, TextureFormat.PRGBA_32bpp );

						mat.NormalMap = texture0;
						textures.Add( texture0 );
					}
					else
					{
						try
						{
							var texture0 = new Texture2D( string.Format( "{0}:{1}:DIFFUSE0", filename, aiMat.Name ), Path.Combine( directory, slot.FilePath ), TextureFormat.PRGBA_32bpp );
							mat.NormalMap = texture0;
							textures.Add( texture0 );
						}
						catch ( FileNotFoundException )
						{

						}
					}
				}

				Color4D ambient = new Color4D( 0.2f, 0.2f, 0.2f, 1.0f ),
					diffuse = new Color4D( 1.0f, 1.0f, 1.0f, 1.0f ),
					specular = new Color4D( 0.0f, 0.0f, 0.0f, 1.0f );
				float specExp = 32.0f;
				if ( aiMat.HasColorAmbient ) ambient = aiMat.ColorAmbient;
				if ( aiMat.HasColorDiffuse ) diffuse = aiMat.ColorDiffuse;
				if ( aiMat.HasColorSpecular ) specular = aiMat.ColorSpecular;
				if ( aiMat.HasShininessStrength ) specExp = aiMat.ShininessStrength;

				mat.Ambient = Average( ambient );
				mat.Diffuse = Average( diffuse );
				mat.Specular = Average( specular );
				mat.SpecExp = specExp;

				materials[i] = mat;
			}
		}
	}
}
