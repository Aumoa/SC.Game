using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets.MDL
{
	partial class Parser
	{
		void ReadBone()
		{
			var bone = new Bone();
			bone.Parent = -1;

			int objectId = 0;
			bone.Name = ReadString();

			ReadChar();  // {

			ForEachTokensInBracket( ( string token ) =>
			{
				int numKeyframes;

				switch ( token )
				{
					case "ObjectId":
						objectId = ReadInt();
						break;
					case "Parent":
						bone.Parent = ReadInt();
						break;
					case "Rotation":
						numKeyframes = ReadInt();

						bone.Rotation.Keys = new List<Keyframe<Quaternion>>();
						ReadChar();  // {

						bone.Rotation.Method = ReadString();

						for ( int i = 0; i < numKeyframes; ++i )
						{
							var key = new Keyframe<Quaternion>();

							var str = ReadString();
							if ( str == "GlobalSeqId" )
							{
								ReadInt();
								i -= 1;
								continue;
							}
							key.IntervalPos = int.Parse( str.Substring( 0, str.Length - 1 ) );
							key.Value = ReadKeyframe4( bone.Rotation.Method );

							bone.Rotation.Keys.Add( key );
						}

						ReadChar();  // }
						break;
					case "Scaling":
						numKeyframes = ReadInt();

						bone.Scale.Keys = new List<Keyframe<Vector3>>();
						ReadChar();  // {

						bone.Scale.Method = ReadString();

						for ( int i = 0; i < numKeyframes; ++i )
						{
							var key = new Keyframe<Vector3>();

							var str = ReadString();
							if ( str == "GlobalSeqId" )
							{
								ReadInt();
								i -= 1;
								continue;
							}
							key.IntervalPos = int.Parse( str.Substring( 0, str.Length - 1 ) );
							key.Value = ReadKeyframe3( bone.Scale.Method );

							bone.Scale.Keys.Add( key );
						}

						ReadChar();  // }
						break;
					case "Translation":
						numKeyframes = ReadInt();

						bone.Translation.Keys = new List<Keyframe<Vector3>>();
						ReadChar();  // {

						bone.Translation.Method = ReadString();

						for ( int i = 0; i < numKeyframes; ++i )
						{
							var key = new Keyframe<Vector3>();

							var str = ReadString();
							if ( str == "GlobalSeqId" )
							{
								ReadInt();
								i -= 1;
								continue;
							}
							key.IntervalPos = int.Parse( str.Substring( 0, str.Length - 1 ) );
							key.Value = ReadKeyframe3( bone.Translation.Method );

							bone.Translation.Keys.Add( key );
						}

						ReadChar();  // }
						break;
				}
			} );

			if ( boneNameReplace.ContainsKey( bone.Name ) )
			{
				bone.Name = bone.Name + "_" + objectId;
			}

			boneNameReplace.Add( bone.Name, bone );
			bones[objectId] = bone;
		}

		void ReadGeosetAnim()
		{
			ForEachTokensInBracket( ( string token ) => { } );
		}

		Geoset ReadGeoset()
		{
			var geoset = new Geoset();

			ReadChar();  // {

			ForEachTokensInBracket( ( string token ) =>
			{
				switch ( token )
				{
					case "Vertices":
						int numVertex = ReadInt();
						geoset.Vertices = new Vector3[numVertex];
						ReadChar();  // {
						for ( int i = 0; i < numVertex; ++i )
						{
							geoset.Vertices[i] = ReadVector3();
						}
						ReadChar();  // }
						break;
					case "Normals":
						int numNormal = ReadInt();
						geoset.Normals = new Vector3[numNormal];
						ReadChar();  // {
						for ( int i = 0; i < numNormal; ++i )
						{
							geoset.Normals[i] = ReadVector3();
						}
						ReadChar();  // }
						break;
					case "TVertices":
						int numTVs = ReadInt();
						geoset.TexCoords = new Vector2[numTVs];
						ReadChar();  // {
						for ( int i = 0; i < numTVs; ++i )
						{
							geoset.TexCoords[i] = ReadVector2();
						}
						ReadChar();  // }
						break;
					case "VertexGroup":
						ReadChar();  // {
						var numGroups = geoset.Vertices.Length;
						geoset.VertexGroups = new int[numGroups];
						for ( int i = 0; i < numGroups; ++i )
						{
							geoset.VertexGroups[i] = ReadInt();
						}
						ReadChar();  // }
						break;
					case "Faces":
						var numTriangles = ReadInt();
						var numIndexes = ReadInt();
						geoset.Faces = new int[numTriangles][];

						ReadChar();  // {
						for ( int i = 0; i < numTriangles; ++i )
						{
							ReadString();
							ReadChar();  // {
							geoset.Faces[i] = ReadTriangles( numIndexes );
							ReadChar();  // }
						}
						ReadChar();  // }
						break;
					case "Groups":
						int numGroups1 = ReadInt();
						int numBoneReference = ReadInt();

						geoset.Groups = new Group[numGroups1];

						ReadChar();  // {
						for ( int i = 0; i < numGroups1; ++i )
						{
							geoset.Groups[i] = new Group();
							geoset.Groups[i].Y = -1;
							geoset.Groups[i].Z = -1;
							geoset.Groups[i].W = -1;

							ReadString();  // Matrices
							ReadChar();  // {
							for ( int j = 0; j < 4; ++j )
							{
								var token1 = ReadString();
								if ( token1 == "}" )
								{
									break;
								}
								else
								{
									var v = int.Parse( token1 );
									if ( j == 0 ) geoset.Groups[i].X = v;
									else if ( j == 1 ) geoset.Groups[i].Y = v;
									else if ( j == 2 ) geoset.Groups[i].Z = v;
									else if ( j == 3 ) geoset.Groups[i].W = v;
								}
							}
						}
						ReadChar();  // }
						break;
					case "MinimumExtent":
						ReadVector3();
						break;
					case "MaximumExtent":
						ReadVector3();
						break;
					case "BoundsRadius":
						ReadSingle();
						break;
					case "Anim":
						ReadChar();
						ForEachTokensInBracket( ( string token1 ) => { } );
						break;
					case "MaterialID":
						geoset.MaterialID = ReadInt();
						break;
					case "SelectionGroup":
						ReadInt();
						break;
				}
			} );

			return geoset;
		}

		int[] ReadTriangles( int numIndexes )
		{
			var triangles = new int[numIndexes];

			ReadChar();  // {
			for ( int i = 0; i < numIndexes; ++i )
			{
				triangles[i] = ReadInt();
			}
			ReadChar();  // }

			return triangles;
		}

		Material ReadMaterial()
		{
			var mat = new Material();
			mat.Layers = new List<Layer>();

			ReadChar();

			ForEachTokensInBracket( ( string token ) =>
			{
				switch ( token )
				{
					case "Layer":
						var layer = new Layer();

						ForEachTokensInBracket( ( string token1 ) =>
						{
							switch ( token1 )
							{
								case "static":
									ReadString();
									layer.TextureID = ReadInt();
									break;
								case "Alpha":
									ReadInt();
									ReadChar();
									ReadChar();
									ForEachTokensInBracket( ( string token2 ) => { } );
									break;
								case "FilterMode":
									layer.FilterMode = ReadString();
									break;
							}
						} );

						mat.Layers.Add( layer );
						break;
					case "ConstantColor":
						mat.ConstantColor = true;
						break;
				}
			} );

			return mat;
		}

		Texture ReadTexture()
		{
			Texture txr = new Texture();

			var str = ReadString();

			if ( str == "Bitmap" )
			{
				ReadChar();

				ForEachTokensInBracket( ( string token ) =>
				{
					switch ( token )
					{
						case "Image":
							txr.Image = ReadString();
							break;
						case "ReplaceableId":
							txr.ReplaceableId = ReadInt();
							break;
					}
				} );
			}
			else
			{
				ForEachTokensInBracket( ( string token ) =>
				{

				} );
			}

			return txr;
		}

		Sequence ReadSequence()
		{
			Sequence seq = new Sequence();

			ReadString();  // ignore
			seq.Anim = ReadString();

			ReadChar();  // {

			ForEachTokensInBracket( ( string token ) =>
			{
				switch ( token )
				{
					case "Interval":
						seq.Interval = ReadInterval();
						break;
					case "NonLooping":
						seq.NonLooping = true;
						break;
				}
			} );

			return seq;
		}

		void ReadModel()
		{
			model.Name = ReadString();

			ReadChar();  // {

			ForEachTokensInBracket( ( string token ) =>
			{
				switch ( token )
				{
					case "NumGeosets":
						model.NumGeosets = ReadInt();
						break;
					case "NumGeosetAnims":
						model.NumGeosetAnims = ReadInt();
						break;
					case "NumHelpers":
						model.NumHelpers = ReadInt();
						break;
					case "NumBones":
						model.NumBones = ReadInt();
						break;
					case "NumAttachments":
						model.NumAttachments = ReadInt();
						break;
					case "BlendTime":
						model.BlendTime = ReadInt();
						break;
					case "MinimumExtent":
						model.MinimumExtent = ReadVector3();
						break;
					case "MaximumExtent":
						model.MaximumExtent = ReadVector3();
						break;
				}
			} );

			bones = new Bone[model.NumBones + model.NumHelpers + model.NumAttachments];
		}

		void ReadVersion()
		{
			ReadChar();  // open bracket

			ForEachTokensInBracket( ( string token ) =>
			{
				switch ( token )
				{
					case "FormatVersion":
						version.FormatVersion = ReadInt();
						break;
				}
			} );
		}
	}
}
