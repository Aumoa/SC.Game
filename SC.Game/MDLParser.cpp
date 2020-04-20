using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Numerics;

using namespace std;
using namespace std::filesystem;

MDLParser::MDLParser( String^ filepath ) : TextParser( " \t,\n\r" )
{
	std::wstring c_str = msclr::interop::marshal_context().marshal_as<const wchar_t*>( filepath );
	std::ifstream file( c_str );

	if ( file.is_open() == false ) throw new exception();

	size_t filesize = ( size_t )file.seekg( 0, ios::end ).tellg();
	file.seekg( 0, ios::beg );

	std::vector<char> buffer( filesize );
	int bufferSeek = 0;

	file.read( buffer.data(), filesize );
	file.close();

	SetBuffer( buffer.data() );
	TryParse();
}

GameObject^ MDLParser::CreateGameObject( String^ name, String^ resourcePath )
{
	auto head = gcnew GameObject( name );

	auto textures = LoadTextures( name, resourcePath );
	auto materials = LoadMaterials( name, textures );
	LoadBones( name, head );
	LoadMeshes( name, head, materials );

	return head;
}

void MDLParser::TryParse()
{
	while ( !Eof )
	{
		auto context = ReadString();

		if ( context == "Version" )
		{
			ReadVersion();
		}
		else if ( context == "Model" )
		{
			ReadModel();
		}
		else if ( context == "Sequences" )
		{
			int numSeqs = ReadInt();
			ReadChar();  // {

			sequences.resize( numSeqs );
			for ( int i = 0; i < numSeqs; ++i )
			{
				sequences[i] = ReadSequence();
			}
			ReadChar();  // }
		}
		else if ( context == "Textures" )
		{
			int numTextures = ReadInt();
			ReadChar();  // {
			textures.resize( numTextures );

			for ( int i = 0; i < numTextures; ++i )
			{
				textures[i] = move( ReadTexture() );
			}
		}
		else if ( context == "Materials" )
		{
			int numMaterials = ReadInt();
			materials.resize( numMaterials );
			ReadChar();  // {
			for ( int i = 0; i < numMaterials; ++i )
			{
				ReadString();
				materials[i] = move( ReadMaterial() );
			}
		}
		else if ( context == "Geoset" )
		{
			double geosetProg = 0.8 / model.NumGeosets;
			geosets.push_back( move( ReadGeoset() ) );
		}
		else if ( context == "GeosetAnim" )
		{
			ReadChar();
			ReadGeosetAnim();
		}
		else if ( context == "Bone" )
		{
			ReadBone();
		}
		else if ( context == "Helper" )
		{
			ReadBone();
		}
		else if ( context == "Attachment" )
		{
			ReadBone();
		}
		else if ( context == "PivotPoints" )
		{
			int numPivots = ReadInt();
			pivots.resize( numPivots );

			ReadChar();  // {
			for ( int i = 0; i < numPivots; ++i )
			{
				pivots[i] = ReadVector3InBracket();
			}
			ReadChar();  // }
		}
		else if ( context == "Camera" )
		{
			ReadString();
			ForEachContextsInBracket();
		}
		else if ( context == "CollisionShape" )
		{
			ReadString();
			ForEachContextsInBracket();
		}
	}
}

void MDLParser::ReadVersion()
{
	ForEachContextsInBracket( [&]( string context )
		{
			if ( context == "FormatVersion" )
			{
				version.FormatVersion = ReadInt();
			}
		}
	);
}

void MDLParser::ReadModel()
{
	model.Name = ReadString();

	ForEachContextsInBracket( [&]( string context )
		{
			if ( context == "NumGeosets" )
			{
				model.NumGeosets = ReadInt();
			}
			else if ( context == "NumGeosetAnims" )
			{
				model.NumGeosets = ReadInt();
			}
			else if ( context == "NumHelpers" )
			{
				model.NumHelpers = ReadInt();
			}
			else if ( context == "NumBones" )
			{
				model.NumBones = ReadInt();
			}
			else if ( context == "NumAttachments" )
			{
				model.NumAttachments = ReadInt();
			}
			else if ( context == "BlendTime" )
			{
				model.BlendTime = ReadInt();
			}
			else if ( context == "MinimumExtent" )
			{
				model.MinimumExtent = ReadVector3InBracket();
			}
			else if ( context == "MaximumExtent" )
			{
				model.MaximumExtent = ReadVector3InBracket();
			}
		}
	);

	geosetAnims.resize( model.NumGeosets );
}

auto MDLParser::ReadGeoset() -> tag_Geoset
{
	tag_Geoset geoset;

	ForEachContextsInBracket( [&]( string context )
		{
			if ( context == "Vertices" )
			{
				int numVertex = ReadInt();
				geoset.Vertices.resize( numVertex );
				ReadChar();  // {
				{
					for ( int i = 0; i < numVertex; ++i )
					{
						geoset.Vertices[i] = ReadVector3InBracket();
					}
				}
				ReadChar();  // }
			}
			else if ( context == "Normals" )
			{
				int numNormal = ReadInt();
				geoset.Normals.resize( numNormal );
				ReadChar();  // {
				{
					for ( int i = 0; i < numNormal; ++i )
					{
						geoset.Normals[i] = ReadVector3InBracket();
					}
				}
				ReadChar();  // }
			}
			else if ( context == "TVertices" )
			{
				int numTVs = ReadInt();
				geoset.TVertices.resize( numTVs );
				ReadChar();  // {
				{
					for ( int i = 0; i < numTVs; ++i )
					{
						geoset.TVertices[i] = ReadVector2InBracket();
					}
				}
				ReadChar();  // }
			}
			else if ( context == "VertexGroup" )
			{
				ReadChar();  // {
				geoset.VertexGroup.resize( geoset.Vertices.size() );
				for ( int i = 0, count = ( int )geoset.Vertices.size(); i < count; ++i )
				{
					geoset.VertexGroup[i] = ReadInt();
				}
				ReadChar();  // }
			}
			else if ( context == "Faces" )
			{
				auto numTriangles = ReadInt();
				auto numIndexes = ReadInt();
				geoset.Faces.resize( numTriangles );

				ReadChar();  // {
				for ( int i = 0; i < numTriangles; ++i )
				{
					ReadString(); ReadChar();  // {
					geoset.Faces[i] = move( ReadTriangles( numIndexes ) );
					ReadChar();  // }
				}
				ReadChar();  // }
			}
			else if ( context == "Groups" )
			{
				int numGroups = ReadInt();
				int numBoneReference = ReadInt();

				geoset.Groups.resize( numGroups );

				ReadChar();  // {
				for ( int i = 0; i < numGroups; ++i )
				{
					auto& group = geoset.Groups[i];

					group.Indices[1] = -1;
					group.Indices[2] = -1;
					group.Indices[3] = -1;

					ReadString();  // Matrices
					ReadChar();  // {
					for ( int i = 0; i < 5; ++i )
					{
						auto token = ReadString();
						if ( token == "}" )
						{
							break;
						}
						else
						{
							stringstream ss( token );
							ss >> group.Indices[i];
						}
					}
				}
				ReadChar();  // }
			}
			else if ( context == "MinimumExtent" )
			{
				ReadVector3InBracket();
			}
			else if ( context == "MaximumExtent" )
			{
				ReadVector3InBracket();
			}
			else if ( context == "BoundsRadius" )
			{
				ReadDouble();
			}
			else if ( context == "Anim" )
			{
				ReadChar();
				DiscardBracketInChildrens();
			}
			else if ( context == "MaterialID" )
			{
				geoset.MaterialID = ReadInt();
			}
			else if ( context == "SelectionGroup" )
			{
				ReadInt();
			}
		}
	);

	return move( geoset );
}

vector<int> MDLParser::ReadTriangles( int numIndexes )
{
	vector<int> triangles( numIndexes );

	ReadChar();  // {
	for ( int i = 0; i < numIndexes; ++i )
	{
		triangles[i] = ReadInt();
	}
	ReadChar();  // }

	return move( triangles );
}

auto MDLParser::ReadTexture() -> tag_Texture
{
	tag_Texture txr;

	auto str = ReadString();
	if ( str == "Bitmap" )
	{
		ForEachContextsInBracket( [&]( string context )
			{
				if ( context == "Image" )
				{
					txr.Image = ReadString();
				}
				else if ( context == "ReplaceableId" )
				{
					txr.ReplaceableId = ReadInt();
				}
			}
		);
	}
	else
	{
		ForEachContextsInBracket();
	}

	return move( txr );
}

auto MDLParser::ReadMaterial() -> tag_Material
{
	tag_Material mtr;

	ForEachContextsInBracket( [&]( string name )
		{
			if ( name == "Layer" )
			{
				tag_Layer layer;

				ForEachContextsInBracket( [&]( string name )
					{
						if ( name == "static" )
						{
							ReadString();
							layer.TextureID = ReadInt();
						}
						else if ( name == "Alpha" )
						{
							ReadInt();
							ReadChar();
							DiscardBracketInChildrens();
						}
						else if ( name == "FilterMode" )
						{
							layer.FilterMode = ReadString();
						}
					}
				);

				mtr.Layer.push_back( move( layer ) );
			}
			else if ( name == "ConstantColor" )
			{
				mtr.ConstantColor = true;
			}
		}
	);

	return move( mtr );
}

auto MDLParser::ReadSequence() -> tag_Sequence
{
	tag_Sequence seq;

	ReadString();
	seq.Anim = ReadString();

	ForEachContextsInBracket( [&]( string context )
		{
			if ( context == "Interval" )
			{
				ReadVector2AsIntInBracket( &seq.Interval.Begin, &seq.Interval.End );
			}
			else if ( context == "NonLooping" )
			{
				seq.NonLooping = true;
			}
		}
	);

	return move( seq );
}

void MDLParser::ReadBone()
{
	if ( bones.size() == 0 )
	{
		bones.resize( model.NumBones + model.NumHelpers + model.NumAttachments );
	}

	tag_Bone bone;

	int objectId = 0;

	bone.Name = ReadString();

	ForEachContextsInBracket( [&]( string token )
		{
			if ( token == "ObjectId" )
			{
				objectId = ReadInt();
			}
			else if ( token == "Parent" )
			{
				bone.Parent = ReadInt();
			}
			else if ( token == "Rotation" )
			{
				int numKeyframes = ReadInt();

				bone.Rotation.Keyframes.resize( numKeyframes );
				ReadChar();  // {

				bone.Rotation.Method = ReadString();

				for ( int i = 0; i < numKeyframes; ++i )
				{
					auto& rot = bone.Rotation.Keyframes[i];

					rot.IntervalPos = ReadInt();
					rot.Value = ReadKeyframe4( bone.Rotation.Method );
				}

				ReadChar();  // }
			}
			else if ( token == "Scaling" )
			{
				int numKeyframes = ReadInt();

				bone.Scale.Keyframes.resize( numKeyframes );
				ReadChar();  // {

				bone.Scale.Method = ReadString();

				for ( int i = 0; i < numKeyframes; ++i )
				{
					auto& rot = bone.Scale.Keyframes[i];

					rot.IntervalPos = ReadInt();
					rot.Value = ReadKeyframe3( bone.Scale.Method );
				}

				ReadChar();  // }
			}
			else if ( token == "Translation" )
			{
				int numKeyframes = ReadInt();

				bone.Translation.Keyframes.resize( numKeyframes );
				ReadChar();  // {

				bone.Translation.Method = ReadString();

				for ( int i = 0; i < numKeyframes; ++i )
				{
					auto& rot = bone.Translation.Keyframes[i];

					rot.IntervalPos = ReadInt();
					rot.Value = ReadKeyframe3( bone.Translation.Method );
				}

				ReadChar();  // }
			}
		}
	);

	if ( auto it = boneNameReplace.find( bone.Name ); it != boneNameReplace.end() )
	{
		stringstream ss;
		ss << bone.Name << '_' << objectId;
		bone.Name = ss.str();
		boneNameReplace.insert( bone.Name );
	}
	else
	{
		boneNameReplace.insert( bone.Name );
	}

	bones[objectId] = move( bone );
}

void MDLParser::ReadGeosetAnim()
{
	ForEachContextsInBracket();
}

XMFLOAT3 MDLParser::ReadVector3InBracket()
{
	ReadChar();  // {
	auto x = ReadDouble();
	auto y = ReadDouble();
	auto z = ReadDouble();
	ReadChar();  // }
	return XMFLOAT3( x, y, z );
}

XMFLOAT2 MDLParser::ReadVector2InBracket()
{
	ReadChar();  // {
	auto x = ReadDouble();
	auto y = ReadDouble();
	ReadChar();  // }
	return XMFLOAT2( x, y );
}

XMFLOAT4 MDLParser::ReadVector4InBracket()
{
	XMFLOAT4 q;

	ReadChar(); // {
	q.x = ReadDouble();
	q.y = ReadDouble();
	q.z = ReadDouble();
	q.w = ReadDouble();
	ReadChar();  // }

	return q;
}

void MDLParser::ReadVector2AsIntInBracket( int* out1, int* out2 )
{
	ReadChar();
	*out1 = ReadInt();
	*out2 = ReadInt();
	ReadChar();
}

XMFLOAT3 MDLParser::ReadKeyframe3( const string& method )
{
	auto ret = ReadVector3InBracket();

	if ( method == "Hermite" )
	{
		ReadString();  // InTan
		ReadVector3InBracket();
		ReadString();  // OutTan
		ReadVector3InBracket();
	}

	return ret;
}

XMFLOAT4 MDLParser::ReadKeyframe4( const string& method )
{
	auto ret = ReadVector4InBracket();

	if ( method == "Hermite" )
	{
		ReadString();  // InTan
		ReadVector4InBracket();
		ReadString();  // OutTan
		ReadVector4InBracket();
	}

	return ret;
}

void MDLParser::ForEachContextsInBracket( function<void( string name )> contextFunctor )
{
	ReadChar();  // {
	while ( true )
	{
		if ( auto ch = ReadChar(); ch == '}' )
		{
			break;
		}
		else if ( ch == '{' )
		{
			DiscardBracketInChildrens();
		}
		else
		{
			Seekpos -= 1;
			contextFunctor( ReadString() );
		}
	}
}

void MDLParser::ForEachContextsInBracket()
{
	ReadChar();  // {
	while ( true )
	{
		if ( auto ch = ReadChar(); ch == '}' )
		{
			break;
		}
		else
		{
			Seekpos -= 1;
			ReadString();
		}
	}
}

void MDLParser::DiscardBracketInChildrens()
{
	while ( true )
	{
		auto ch = ReadChar();

		if ( ch == '{' )
		{
			DiscardBracketInChildrens();
		}
		else if ( ch == '}' )
		{
			break;
		}
	}
}

IList<Texture2D^>^ MDLParser::LoadTextures( String^ name, String^ resourcePath )
{
	auto txr = gcnew List<Texture2D^>();

	for ( int i = 0; i < ( int )textures.size(); ++i )
	{
		try
		{
			txr->Add( gcnew Texture2D( String::Format( "{0}:Texture{1}", name, i ), String::Format( "{0}/{1}", resourcePath, msclr::interop::marshal_as<String^>( textures[i].Image.c_str() ) ), TextureFormat::PRGBA_32bpp ) );
			//AssetBundle::AddItem( txr[i] );
		}
		catch ( Exception^ e )
		{
			txr->Add( nullptr );
			delete e;
		}
	}

	return txr;
}

IList<Material^>^ MDLParser::LoadMaterials( String^ name, IList<Texture2D^>^ txr )
{
	auto mtr = gcnew List<Material^>();

	for ( int i = 0; i < ( int )materials.size(); ++i )
	{
		mtr->Add( gcnew Material( String::Format( "{0}:Texture{1}", name, i ) ) );

		if ( materials[i].Layer[0].TextureID != -1 )
		{
			mtr[i]->DiffuseMap = txr[materials[i].Layer[0].TextureID];
		}

		if ( materials[i].Layer[0].FilterMode == "Transparent" )
		{
			//mtr[i]->Layer = RenderQueueLayer::Transparent;
		}
		else if ( materials[i].Layer[0].FilterMode == "Additive" )
		{
			//mtr[i]->Layer = RenderQueueLayer::Additive;
		}

		//AssetBundle::AddItem( mtr[i] );
	}

	return mtr;
}

void MDLParser::LoadBones( String^ name, GameObject^ head )
{
	auto gameObjects = gcnew List<GameObject^>();

	auto root = gcnew GameObject( name + ":bone:root" );
	auto bone = root->AddComponent<Bone^>();

	bone->Name = "root";
	bone->Index = ( int )bones.size();

	for ( int i = 0, count = ( int )bones.size(); i < count; ++i )
	{
		auto go = gcnew GameObject( name + ":bone" + i );

		Vector3 pivot;
		pivot.X = -pivots[i].y;
		pivot.Y = pivots[i].z;
		pivot.Z = pivots[i].x;

		auto trp = go->Transform;
		trp->LocalPosition = -pivot;

		auto bone = go->AddComponent<Bone^>();
		bone->Name = msclr::interop::marshal_context().marshal_as<String^>( bones[i].Name.c_str() );
		bone->Index = i;

		gameObjects->Add( go );
	}

	for ( int i = 0, count = ( int )bones.size(); i < count; ++i )
	{
		auto par = bones[i].Parent;

		if ( par == -1 )
		{
			gameObjects[i]->Transform->Parent = root->Transform;
		}
		else
		{
			gameObjects[i]->Transform->Parent = gameObjects[par]->Transform;
		}
	}

	root->Transform->Parent = head->Transform;
}

void MDLParser::LoadMeshes( String^ name, GameObject^ head, IList<Material^>^ mtr )
{
	for ( int i = 0, count = ( int )geosets.size(); i < count; ++i )
	{
		auto& geoset = geosets[i];

		auto gameObject = gcnew GameObject( name + i );

		if ( model.NumBones == 0 )
		{
			vector<Vertex> vertexBuffer( geoset.Vertices.size() );
			for ( int i = 0, count = ( int )geoset.Vertices.size(); i < count; ++i )
			{
				auto& vertex = geoset.Vertices[i];
				auto& normal = geoset.Normals[i];
				auto& uv = geoset.TVertices[i];

				Vertex v;
				v.Pos = { -( float )vertex.y, ( float )vertex.z, ( float )vertex.x };
				v.Normal = { -( float )normal.y, ( float )normal.z, ( float )normal.x };
				v.Tex = { ( float )uv.x, ( float )uv.y };
				v.Color = { 1.0f, 1.0f, 1.0f, 1.0f };

				vertexBuffer[i] = v;
			}

			vector<UINT> indexBuffer( geoset.Faces[0].size() );
			for ( int i = 0, count = ( int )geoset.Faces[0].size(); i < count; i += 1 )
			{
				auto& face = ( int( & )[3] )geoset.Faces[0][i];
				indexBuffer[i + 0] = face[0];
				indexBuffer[i + 1] = face[2];
				indexBuffer[i + 2] = face[1];
			}

			auto mesh = gcnew Mesh( String::Format( "{0}:Mesh{1}", name, i ) );
			mesh->Initialize( vertexBuffer, indexBuffer );
			//AssetBundle::AddItem( mesh );

			auto meshFilter = gameObject->AddComponent<MeshFilter^>();
			meshFilter->Mesh = mesh;
			auto meshRenderer = gameObject->AddComponent<MeshRenderer^>();
			meshRenderer->Material = mtr[geoset.MaterialID];
		}
		else
		{
			vector<SkinnedVertex> vertexBuffer( geoset.Vertices.size() );
			for ( int i = 0, count = ( int )geoset.Vertices.size(); i < count; ++i )
			{
				auto& vertex = geoset.Vertices[i];
				auto& normal = geoset.Normals[i];
				auto& uv = geoset.TVertices[i];
				auto& group = geoset.Groups[geoset.VertexGroup[i]];

				SkinnedVertex v{ };
				v.Pos = { -( float )vertex.y, ( float )vertex.z, ( float )vertex.x };
				v.Normal = { -( float )normal.y, ( float )normal.z, ( float )normal.x };
				v.Tex = { ( float )uv.x, ( float )uv.y };
				v.Color = { 1.0f, 1.0f, 1.0f, 1.0f };

				int numRef = 0;
				for ( int i = 0; i < 4; ++i )
				{
					if ( group.Indices[i] != -1 )
					{
						numRef += 1;
						v.Indices[i] = ( UINT16 )group.Indices[i];
					}
				}

				float weight = 1.0f / numRef;
				for ( int i = 0; i < min( numRef, 3 ); ++i )
				{
					( ( float* )&v.Weights )[i] = weight;
				}

				vertexBuffer[i] = v;
			}

			vector<UINT> indexBuffer( geoset.Faces[0].size() );
			for ( int i = 0, count = ( int )geoset.Faces[0].size(); i < count; i += 3 )
			{
				auto& face = ( int( & )[3] )geoset.Faces[0][i];
				indexBuffer[i + 0] = face[0];
				indexBuffer[i + 1] = face[2];
				indexBuffer[i + 2] = face[1];
			}

			auto mesh = gcnew Mesh( String::Format( "{0}:Mesh{1}", name, i ) );
			mesh->Initialize( vertexBuffer, indexBuffer );
			//AssetBundle::AddItem( mesh );

			auto meshRenderer = gameObject->AddComponent<SkinnedMeshRenderer^>();
			meshRenderer->Material = mtr[geoset.MaterialID];
			meshRenderer->Mesh = mesh;
		}

		gameObject->Transform->Parent = head->Transform;
	}
}