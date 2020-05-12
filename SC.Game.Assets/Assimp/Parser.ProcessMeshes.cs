using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

using SDK = Assimp;
using Assimp.Unmanaged;

namespace SC.Game.Assets.Assimp
{
	partial class Parser
	{
		void ProcessMeshes()
		{
			meshes = new Mesh[scene.MeshCount];

			for ( int i = 0; i < scene.MeshCount; ++i )
			{
				var aiMesh = scene.Meshes[i];
				Game.Mesh mesh;

				if ( aiMesh.BoneCount != 0 )
				{
					var vertexBuffer = new SkinnedVertex[aiMesh.VertexCount];

					for ( int j = 0; j < vertexBuffer.Length; ++j )
					{
						var v = new SkinnedVertex
						{
							Color = new Vector4( 1.0f, 1.0f, 1.0f, 1.0f )
						};

						Assign( out v.Pos, aiMesh.Vertices[j] );
						if ( aiMesh.HasNormals ) Assign( out v.Normal, aiMesh.Normals[j] );
						if ( aiMesh.HasTextureCoords( 0 ) ) Assign( out v.Tex, aiMesh.TextureCoordinateChannels[0][j] );
						if ( aiMesh.HasTangentBasis ) Assign( out v.Tangent, aiMesh.Tangents[j] );
						if ( aiMesh.HasVertexColors( 0 ) ) Assign( out v.Color, aiMesh.VertexColorChannels[0][j] );

						vertexBuffer[j] = v;
					}

					var indexBuffer = new uint[aiMesh.FaceCount * 3];
					for ( int j = 0; j < aiMesh.FaceCount; ++j )
					{
						var face = aiMesh.Faces[j];
						indexBuffer[j * 3 + 0] = ( uint )face.Indices[0];
						indexBuffer[j * 3 + 1] = ( uint )face.Indices[1];
						indexBuffer[j * 3 + 2] = ( uint )face.Indices[2];
					}

					var jointStart = joints.Count;
					for ( int j = 0; j < aiMesh.BoneCount; ++j )
					{
						var bone = aiMesh.Bones[j];
						var jointId = jointStart + j;

						var joint = new Joint();
						joint.Name = bone.Name;
						joint.Offset = bone.OffsetMatrix;

						for ( int k = 0; k < bone.VertexWeightCount; ++k )
						{
							var weights = bone.VertexWeights[k];
							var v = vertexBuffer[weights.VertexID];
							AddJointIndex( ref v, jointId, weights.Weight );
						}
					}

					mesh = Game.Mesh.CreateMesh( string.Format( "{0}:{1}", filename, aiMesh.Name ), vertexBuffer, indexBuffer );
					var mesh1 = new Mesh();
					mesh1.pMesh = mesh;
					mesh1.JointStart = jointStart;
					mesh1.JointCount = aiMesh.BoneCount;

					meshes[i] = mesh1;
				}
				else
				{
					var vertexBuffer = new Vertex[aiMesh.VertexCount];

					for ( int j = 0; j < vertexBuffer.Length; ++j )
					{
						var v = new Vertex
						{
							Color = new Vector4( 1.0f, 1.0f, 1.0f, 1.0f )
						};

						Assign( out v.Pos, aiMesh.Vertices[j] );
						if ( aiMesh.HasNormals ) Assign( out v.Normal, aiMesh.Normals[j] );
						if ( aiMesh.HasTextureCoords( 0 ) ) Assign( out v.Tex, aiMesh.TextureCoordinateChannels[0][j] );
						if ( aiMesh.HasTangentBasis ) Assign( out v.Tangent, aiMesh.Tangents[j] );
						if ( aiMesh.HasVertexColors( 0 ) ) Assign( out v.Color, aiMesh.VertexColorChannels[0][j] );

						vertexBuffer[j] = v;
					}

					var indexBuffer = new uint[aiMesh.FaceCount * 3];
					for ( int j = 0; j < aiMesh.FaceCount; ++j )
					{
						var face = aiMesh.Faces[j];
						indexBuffer[j * 3 + 0] = ( uint )face.Indices[0];
						indexBuffer[j * 3 + 1] = ( uint )face.Indices[1];
						indexBuffer[j * 3 + 2] = ( uint )face.Indices[2];
					}

					mesh = Game.Mesh.CreateMesh( string.Format( "{0}:{1}", filename, aiMesh.Name ), vertexBuffer, indexBuffer );
					var mesh1 = new Mesh();
					mesh1.pMesh = mesh;
					mesh1.JointStart = 0;
					mesh1.JointCount = 0;

					meshes[i] = mesh1;
				}

				var go = new GameObject( aiMesh.Name );
				if ( aiMesh.BoneCount != 0 )
				{
					var skinnedMeshRenderer = go.AddComponent<SkinnedMeshRenderer>();
					skinnedMeshRenderer.Mesh = mesh;
					skinnedMeshRenderer.Material = materials[aiMesh.MaterialIndex];
				}
				else
				{
					go.AddComponent<MeshFilter>().Mesh = mesh;
					go.AddComponent<MeshRenderer>().Material = materials[aiMesh.MaterialIndex];
				}

				go.Transform.Parent = head.Transform;
			}
		}
	}
}
