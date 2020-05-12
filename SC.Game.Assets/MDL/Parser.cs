using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Security.Cryptography;

namespace SC.Game.Assets.MDL
{
	partial class Parser : TextParser
	{
		string filepath;

		Version version;
		Model model;
		Sequence[] sequences;
		Texture[] textures;
		Material[] materials;
		List<Geoset> geosets;
		Bone[] bones;
		Dictionary<string, Bone> boneNameReplace;
		Vector3[] pivots;

		public Parser( string filepath ) : base( " \t,\n\r" )
		{
			this.filepath = filepath;

			TextBuffer = File.ReadAllText( filepath );

			geosets = new List<Geoset>();
			boneNameReplace = new Dictionary<string, Bone>();
		}

		public override LoadedInfo Compose()
		{
			string name = Path.GetFileNameWithoutExtension( filepath );
			string filename = Path.GetFileName( filepath );
			string directory = Path.GetDirectoryName( filepath );

			var head = new GameObject( name );

			var textures = LoadTextures( name, directory );
			var materials = LoadMaterials( name, textures );
			LoadBones( name, head );
			var meshes = LoadMeshes( name, filename, head, materials );
			var clips = LoadAnimationClips( filename );

			var animatorController = new AnimatorController( string.Format( "{0}:AnimatorController", filename ) );

			for ( int i = 0; i < clips.Length; ++i )
			{
				var state = new AnimationState( sequences[i].Anim );
				state.Clip = clips[i];

				animatorController.AddState( state, i == 0 );
			}

			var animator = head.AddComponent<Animator>();
			animator.Controller = animatorController;

			var loadedInfo = new LoadedInfo();
			loadedInfo.Composed = head;
			loadedInfo.Meshes = meshes;
			loadedInfo.AnimationClips = clips;
			loadedInfo.Materials = materials;
			loadedInfo.Textures = textures;

			return loadedInfo;
		}

		AnimationClip[] LoadAnimationClips( string filename )
		{
			if ( sequences.Length != 0 )
			{
				var clips = new AnimationClip[sequences.Length];

				var numAnimationClips = sequences.Length;
				var numBones = bones.Length;

				for ( int i = 0; i < numAnimationClips; ++i )
				{
					var clip = new AnimationClip( string.Format( "{0}:{1}", filename, sequences[i].Anim ) );

					var seq = sequences[i];

					for ( int j = 0; j < numBones; ++j )
					{
						var bone = bones[j];

						Keyframes keyf;
						var boneName = bone.Name;

						Keyframes<Vector3> translation;
						Keyframes<Vector3> scale;
						Keyframes<Quaternion> rotation;

						bone.Export( seq.Interval, out translation, out scale, out rotation );

						keyf.Translation = new List<Keyframe>( translation.Keys.Count );
						keyf.Scaling = new List<Keyframe>( scale.Keys.Count );
						keyf.Rotation = new List<KeyframeQ>( rotation.Keys.Count );

						Vector3 pivotdel = pivots[j];
						if ( bone.Parent != -1 )
						{
							pivotdel.X -= pivots[bone.Parent].X;
							pivotdel.Y -= pivots[bone.Parent].Y;
							pivotdel.Z -= pivots[bone.Parent].Z;
						}
						pivotdel = RecomposeVector( pivotdel );

						if ( translation.Keys.Count == 0 )
						{
							keyf.Translation.Add( new Keyframe( 0.0f, pivotdel ) );
						}
						else
						{
							for ( int k = 0; k < translation.Keys.Count; ++k )
							{
								var tp = ( translation.Keys[k].IntervalPos - seq.Interval.Begin ) / 1000.0f;
								var value = RecomposeVector( translation.Keys[k].Value ) + pivotdel;

								keyf.Translation.Add( new Keyframe( tp, value ) );
							}
						}

						for ( int k = 0; k < scale.Keys.Count; ++k )
						{
							var tp = ( scale.Keys[k].IntervalPos - seq.Interval.Begin ) / 1000.0f;
							var value = RecomposeVector( scale.Keys[k].Value );

							keyf.Scaling.Add( new Keyframe( tp, value ) );
						}

						for ( int k = 0; k < rotation.Keys.Count; ++k )
						{
							var tp = ( rotation.Keys[k].IntervalPos - seq.Interval.Begin ) / 1000.0f;
							var value = RecomposeQuaternion( rotation.Keys[k].Value );

							keyf.Rotation.Add( new KeyframeQ( tp, value ) );
						}

						clip.AddKeyframes( boneName, keyf );
					}

					clip.IsLoop = !seq.NonLooping;
					clips[i] = clip;
				}

				return clips;
			}
			else
			{
				return null;
			}
		}

		Mesh[] LoadMeshes( string name, string filename, GameObject head, IList<Game.Material> materials )
		{
			Mesh[] meshes = new Mesh[geosets.Count];

			for ( int i = 0; i < geosets.Count; ++i )
			{
				var gameObject = new GameObject( name + ":Mesh" + i );

				if ( model.NumBones == 0 )
				{
					var geoset = geosets[i];

					Vertex[] vertexBuffer = new Vertex[geoset.Vertices.Length];
					for ( int j = 0; j < vertexBuffer.Length; ++j )
					{
						var vertex = geoset.Vertices[j];
						var normal = geoset.Normals[j];

						var v = new Vertex
						{
							Pos = new Vector3( -vertex.Y, vertex.Z, vertex.X ),
							Normal = new Vector3( -normal.Y, normal.Z, normal.X ),
							Tex = geoset.TexCoords[j],
							Color = new Vector4( 1.0f, 1.0f, 1.0f, 1.0f )
						};

						vertexBuffer[j] = v;
					}

					uint[] indexBuffer = new uint[geoset.Faces[0].Length];
					for ( int j = 0; j < indexBuffer.Length; j += 3 )
					{
						indexBuffer[j + 0] = ( uint )geoset.Faces[0][j + 0];
						indexBuffer[j + 1] = ( uint )geoset.Faces[0][j + 1];
						indexBuffer[j + 2] = ( uint )geoset.Faces[0][j + 2];
					}

					var mesh = Mesh.CreateMesh( string.Format( "{0}:Mesh{1}", filename, i ), vertexBuffer, indexBuffer );

					var meshFilter = gameObject.AddComponent<MeshFilter>();
					meshFilter.Mesh = mesh;
					var meshRenderer = gameObject.AddComponent<MeshRenderer>();
					meshRenderer.Material = materials[geoset.MaterialID];

					meshes[i] = mesh;
				}
				else  // IsSkinned
				{
					var geoset = geosets[i];

					SkinnedVertex[] vertexBuffer = new SkinnedVertex[geoset.Vertices.Length];
					for ( int j = 0; j < vertexBuffer.Length; ++j )
					{
						var vertex = geoset.Vertices[j];
						var normal = geoset.Normals[j];

						var v = new SkinnedVertex
						{
							Pos = new Vector3( -vertex.Y, vertex.Z, vertex.X ),
							Normal = new Vector3( -normal.Y, normal.Z, normal.X ),
							Tex = geoset.TexCoords[j],
							Color = new Vector4( 1.0f, 1.0f, 1.0f, 1.0f )
						};

						int numRef = 1;
						var group = geoset.Groups[geoset.VertexGroups[j]];

						v.Indices.X = group.X;
						if ( group.Y != -1 )
						{
							v.Indices.Y = group.Y;
							numRef += 1;
						}
						if ( group.Z != -1 )
						{
							v.Indices.Z = group.Z;
							numRef += 1;
						}
						if ( group.W != -1 )
						{
							v.Indices.W = group.W;
							numRef += 1;
						}

						float weight = 1.0f / numRef;
						v.Weights.X = weight;
						v.Weights.Y = weight;
						v.Weights.Z = weight;

						vertexBuffer[j] = v;
					}

					uint[] indexBuffer = new uint[geoset.Faces[0].Length];
					for ( int j = 0; j < indexBuffer.Length; j += 3 )
					{
						indexBuffer[j + 0] = ( uint )geoset.Faces[0][j + 0];
						indexBuffer[j + 1] = ( uint )geoset.Faces[0][j + 1];
						indexBuffer[j + 2] = ( uint )geoset.Faces[0][j + 2];
					}

					var mesh = Mesh.CreateMesh( string.Format( "{0}:Mesh{1}", filename, i ), vertexBuffer, indexBuffer );

					var meshRenderer = gameObject.AddComponent<SkinnedMeshRenderer>();
					meshRenderer.Mesh = mesh;
					meshRenderer.Material = materials[geoset.MaterialID];

					meshes[i] = mesh;
				}

				gameObject.Transform.Parent = head.Transform;
			}

			return meshes;
		}

		void LoadBones( string name, GameObject head )
		{
			var gameObjects = new List<GameObject>();

			var root = new GameObject( name + ":bone:root" );
			var bone = root.AddComponent<Game.Bone>();

			bone.Name = "root";
			bone.Index = bones.Length;

			for ( int i = 0; i < bones.Length; ++i )
			{
				var go = new GameObject( name + ":bone" + i );

				Vector3 pivot;
				pivot.X = -pivots[i].Y;
				pivot.Y = pivots[i].Z;
				pivot.Z = pivots[i].X;

				var bone1 = go.AddComponent<Game.Bone>();
				bone1.Name = bones[i].Name;
				bone1.Index = i;
				bone1.Offset = Matrix4x4.CreateTranslation( pivot.X, pivot.Y, pivot.Z );

				gameObjects.Add( go );
			}

			for ( int i = 0; i < bones.Length; ++i )
			{
				var par = bones[i].Parent;

				if ( par == -1 ) gameObjects[i].Transform.Parent = root.Transform;
				else gameObjects[i].Transform.Parent = gameObjects[par].Transform;
			}

			root.Transform.Parent = head.Transform;
		}

		Game.Material[] LoadMaterials( string name, Texture2D[] textures )
		{
			var materials = new Game.Material[this.materials.Length];

			for ( int i = 0; i < materials.Length; ++i )
			{
				var mat = new Game.Material( string.Format( "{0}:Texture{1}", name, i ) );
				
				if ( this.materials[i].Layers[0].TextureID != -1 )
				{
					mat.DiffuseMap = textures[this.materials[i].Layers[0].TextureID];
				}

				materials[i] = mat;
			}

			return materials;
		}

		Texture2D[] LoadTextures( string name, string directory )
		{
			var textures = new Texture2D[this.textures.Length];

			for ( int i = 0; i < textures.Length; ++i )
			{
				try
				{
					textures[i] = new Texture2D(
						string.Format( "{0}:Texture{1}", name, i ),
						string.Format( "{0}/{1}", directory, this.textures[i].Image ),
						TextureFormat.PRGBA_32bpp
						);
				}
				catch ( FileNotFoundException )
				{

				}
			}

			return textures;
		}

		public override void TryParse()
		{
			string token;

			while ( ( token = ReadString() ) != null )
			{
				switch ( token )
				{
					case "Version":
						ReadVersion();
						break;
					case "Model":
						ReadModel();
						break;
					case "Sequences":
						ReadSequences();
						break;
					case "Textures":
						ReadTextures();
						break;
					case "Materials":
						ReadMaterials();
						break;
					case "Geoset":
						geosets.Add( ReadGeoset() );
						break;
					case "GeosetAnim":
						ReadChar();
						ReadGeosetAnim();
						break;
					case "Bone":
					case "Helper":
					case "Attachment":
						ReadBone();
						break;
					case "PivotPoints":
						ReadPivots();
						break;
					case "Camera":
						ReadString();
						ReadChar();
						ForEachTokensInBracket( ( string token1 ) => { } );
						break;
					case "CollisionShape":
						ReadString();
						ReadChar();
						ForEachTokensInBracket( ( string token1 ) => { } );
						break;
				}
			}
		}

		void ReadPivots()
		{
			int numPivots = ReadInt();
			pivots = new Vector3[numPivots];

			ReadChar();
			for ( int i = 0; i < numPivots; ++i )
			{
				pivots[i] = ReadVector3();
			}
			ReadChar();
		}

		void ReadMaterials()
		{
			int numMaterials = ReadInt();
			materials = new Material[numMaterials];
			ReadChar();

			for ( int i = 0; i < numMaterials; ++i )
			{
				ReadString();
				materials[i] = ReadMaterial();
			}
		}

		void ReadTextures()
		{
			int numTextures = ReadInt();

			ReadChar();
			textures = new Texture[numTextures];

			for ( int i = 0; i < numTextures; ++i )
			{
				textures[i] = ReadTexture();
			}
		}

		void ReadSequences()
		{
			int numSequences = ReadInt();
			ReadChar();  // {

			sequences = new Sequence[numSequences];
			for ( int i = 0; i < numSequences; ++i )
			{
				sequences[i] = ReadSequence();
			}
			ReadChar();  // }
		}
	}
}
