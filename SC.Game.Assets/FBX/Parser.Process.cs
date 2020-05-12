using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using FbxSDK;

using M = System.Numerics;

namespace SC.Game.Assets.FBX
{
	partial class Parser
	{
		void ProcessNode( Node node, GameObject head, int parentIndex )
		{
			var gameObject = new GameObject( node.Name );
			var transform = gameObject.Transform;

			transform.Parent = head.Transform;
			transform.LocalPosition = node.Position;
			transform.LocalScale = node.Scale;
			transform.LocalRotation = node.Rotation;

			ReadJoint( node, gameObject );

			var numMeshes = node.MeshCount;
			for ( int i = 0; i < numMeshes; ++i )
			{
				var split = new GameObject( "Split Mesh " + i );
				split.Transform.Parent = gameObject.Transform;

				ReadMesh( node.GetMeshAttribute( i ), split );
			}

			for ( int i = 0; i < node.NumChilds; ++i )
			{
				ProcessNode( node.GetChild( i ), gameObject, parentIndex );
			}
		}

		void ReadJoint( Node node, GameObject gameObject )
		{
			for ( int i = 0; i < joints.Count; ++i )
			{
				if ( joints[i].Name == node.Name )
				{
					var bone = gameObject.GetComponent<Bone>();
					if ( bone == null )
					{
						bone = gameObject.AddComponent<Bone>();
					}
					else
					{
						var clone = new GameObject( gameObject.Name + " Clone" );
						bone = clone.AddComponent<Bone>();
						clone.Transform.Parent = gameObject.Transform.Parent;
					}

					var joint = joints[i];

					bone.Name = joint.Name;
					bone.Index = i;
					bone.Offset = joint.Offset;

					if ( joint.ParentIndex != -1 )
					{
						M.Matrix4x4.Invert( joints[joint.ParentIndex].Transform, out var invert );
						bone.ToRoot = joint.Transform * invert;
					}
					else
					{
						bone.ToRoot = joint.Transform;
					}
				}
			}
		}

		void ProcessMaterials()
		{
			materials = new Material[scene.NumMaterials];
			for ( int i = 0; i < materials.Length; ++i )
			{
				var material = scene.GetMaterial( i );

				materials[i] = new Material( filename + ":Material" + i );
				materials[i].Ambient = material.Ambient;
				materials[i].Diffuse = material.Diffuse;
				materials[i].Specular = material.Specular;
				materials[i].SpecExp = material.Shininess;

				try
				{
					if ( material.DiffuseMap != null )
					{
						var filename = Path.GetFileName( material.DiffuseMap );
						var ext = Path.GetExtension( filename );

						if ( ext == ".tga" )
						{
							filename = Path.ChangeExtension( filename, ".png" );
						}

						if ( textures.ContainsKey( filename ) )
						{
							materials[i].DiffuseMap = textures[filename];
						}
						else
						{
							Texture2D texture;
							textures.Add( filename, texture = new Texture2D( filename, texturePaths[filename], TextureFormat.PRGBA_32bpp ) );
							materials[i].DiffuseMap = texture;
						}
					}
					if ( material.NormalMap != null )
					{
						var filename = Path.GetFileName( material.DiffuseMap );
						var ext = Path.GetExtension( filename );

						if ( ext == ".tga" )
						{
							filename = Path.ChangeExtension( filename, ".png" );
						}

						if ( textures.ContainsKey( filename ) )
						{
							materials[i].NormalMap = textures[filename];
						}
						else
						{
							Texture2D texture;
							textures.Add( filename, texture = new Texture2D( filename, texturePaths[filename], TextureFormat.PRGBA_32bpp ) );
							materials[i].NormalMap = textures[filename];
						}
					}
				}
				catch ( KeyNotFoundException )
				{

				}
			}
		}

		void ReadMesh( FbxSDK.Mesh mesh, GameObject gameObject )
		{
			Mesh m;

			if ( mesh.IsSkinned )
			{
				var vertexBuffer = mesh.SkinnedVertexBuffer;
				var indexBuffer = new uint[vertexBuffer.Length];
				for ( int i = 0; i < vertexBuffer.Length; ++i ) indexBuffer[i] = ( uint )i;

				m = Mesh.CreateMesh( string.Format( "{0}:Mesh", filename ), vertexBuffer, indexBuffer );

				var skinnedMeshRenderer = gameObject.AddComponent<SkinnedMeshRenderer>();
				skinnedMeshRenderer.Mesh = m;
				skinnedMeshRenderer.Material = materials[mesh.MaterialIndex];
				isSkinned = true;
			}
			else
			{
				var vertexBuffer = mesh.VertexBuffer;
				var indexBuffer = new uint[vertexBuffer.Length];
				for ( int i = 0; i < vertexBuffer.Length; ++i ) indexBuffer[i] = ( uint )i;

				m = Mesh.CreateMesh( string.Format( "{0}:Mesh", filename ), vertexBuffer, indexBuffer );

				gameObject.AddComponent<MeshFilter>().Mesh = m;
				gameObject.AddComponent<MeshRenderer>().Material = materials[mesh.MaterialIndex];
			}
			meshes.Add( m );

			//gameObject.Transform.Parent = head.Transform;
			fbxMeshes.Add( mesh );
		}
	}
}
