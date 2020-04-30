#pragma once

namespace SC::Game
{
	ref class GameObject;
	ref class Texture2D;
	ref class Material;

	class MDLParser : public TextParser
	{
		std::set<std::string> boneNameReplace;

	public:
		struct tag_Interval
		{
			int Begin;
			int End;
		};

		struct tag_Sequence
		{
			std::string Anim;
			tag_Interval Interval;
			bool NonLooping = false;
		};

		struct tag_Version
		{
			int FormatVersion;
		};

		struct tag_Model
		{
			std::string Name;
			int NumGeosets = 0;
			int NumGeosetAnims = 0;
			int NumHelpers = 0;
			int NumBones = 0;
			int NumAttachments = 0;
			int BlendTime = 0;
			XMFLOAT3 MinimumExtent;
			XMFLOAT3 MaximumExtent;
		};

		struct tag_Group
		{
			int Indices[4];
		};

		struct tag_Geoset
		{
			std::vector<XMFLOAT3> Vertices;
			std::vector<XMFLOAT3> Normals;
			std::vector<XMFLOAT2> TVertices;
			std::vector<int> VertexGroup;
			std::vector<std::vector<int>> Faces;
			std::vector<tag_Group> Groups;
			int MaterialID;
		};

		struct tag_Texture
		{
			std::string Image;
			int ReplaceableId = 0;
		};

		struct tag_Layer
		{
			std::string FilterMode;
			int TextureID = -1;
		};

		struct tag_Material
		{
			bool ConstantColor = false;
			std::vector<tag_Layer> Layer;
		};

		template< class ValueType >
		struct tag_Key
		{
			int IntervalPos;
			ValueType Value;
		};

		template< class ValueType >
		struct tag_Keyframe
		{
			std::string Method;
			std::vector<tag_Key<ValueType>> Keyframes;
		};

		struct tag_Bone
		{
			std::string Name;
			int Parent = -1;
			tag_Keyframe<XMFLOAT3> Translation;
			tag_Keyframe<XMFLOAT3> Scale;
			tag_Keyframe<XMFLOAT4> Rotation;

			void Export( tag_Interval interval, tag_Keyframe<XMFLOAT3>& translation, tag_Keyframe<XMFLOAT3>& scale, tag_Keyframe<XMFLOAT4>& rotation )
			{
				int numKeyf = ( int )Translation.Keyframes.size();
				translation.Method = Translation.Method;
				for ( int i = 0; i < numKeyf; ++i )
				{
					if ( Translation.Keyframes[i].IntervalPos >= interval.Begin && Translation.Keyframes[i].IntervalPos <= interval.End )
					{
						translation.Keyframes.push_back( Translation.Keyframes[i] );
					}
				}

				numKeyf = ( int )Scale.Keyframes.size();
				scale.Method = Scale.Method;
				for ( int i = 0; i < numKeyf; ++i )
				{
					if ( Scale.Keyframes[i].IntervalPos >= interval.Begin && Scale.Keyframes[i].IntervalPos <= interval.End )
					{
						scale.Keyframes.push_back( Scale.Keyframes[i] );
					}
				}

				numKeyf = ( int )Rotation.Keyframes.size();
				rotation.Method = Rotation.Method;
				for ( int i = 0; i < numKeyf; ++i )
				{
					if ( Rotation.Keyframes[i].IntervalPos >= interval.Begin && Rotation.Keyframes[i].IntervalPos <= interval.End )
					{
						rotation.Keyframes.push_back( Rotation.Keyframes[i] );
					}
				}
			}
		};

		struct tag_GeosetAnim
		{
			int GeosetId;
			tag_Keyframe<bool> Keyframes;

			void Export( tag_Interval interval, tag_Keyframe<bool>& alpha )
			{
				int numKeyf = ( int )Keyframes.Keyframes.size();
				Keyframes.Method = Keyframes.Method;
				for ( int i = 0; i < numKeyf; ++i )
				{
					if ( Keyframes.Keyframes[i].IntervalPos >= interval.Begin && Keyframes.Keyframes[i].IntervalPos <= interval.End )
					{
						Keyframes.Keyframes.push_back( Keyframes.Keyframes[i] );
					}
				}
			}
		};

		tag_Version version;
		tag_Model model;
		std::vector<tag_Sequence> sequences;
		std::vector<tag_Texture> textures;
		std::vector<tag_Material> materials;
		std::vector<tag_Geoset> geosets;
		std::vector<tag_Bone> bones;
		std::vector<XMFLOAT3> pivots;
		std::vector<tag_GeosetAnim> geosetAnims;

	public:
		MDLParser( System::String^ filepath );

		GameObject^ CreateGameObject( System::String^ name, System::String^ resourcePath );

	private:
		void TryParse();
		void ReadVersion();
		void ReadModel();
		tag_Geoset ReadGeoset();
		std::vector<int> ReadTriangles( int numIndexes );
		tag_Texture ReadTexture();
		tag_Material ReadMaterial();
		tag_Sequence ReadSequence();
		void ReadBone();
		void ReadGeosetAnim();

		XMFLOAT3 ReadVector3InBracket();
		XMFLOAT2 ReadVector2InBracket();
		XMFLOAT4 ReadVector4InBracket();
		void ReadVector2AsIntInBracket( int* out1, int* out2 );
		XMFLOAT3 ReadKeyframe3( const std::string& method );
		XMFLOAT4 ReadKeyframe4( const std::string& method );

		void ForEachContextsInBracket( std::function<void( std::string context )> contextFunctor );
		void ForEachContextsInBracket();
		void DiscardBracketInChildrens();

		System::Collections::Generic::IList<Texture2D^>^ LoadTextures( System::String^ name, System::String^ resourcePath );
		System::Collections::Generic::IList<Material^>^ LoadMaterials( System::String^ name, System::Collections::Generic::IList<Texture2D^>^ txr );
		void LoadBones( System::String^ name, GameObject^ head );
		void LoadMeshes( System::String^ name, GameObject^ head, System::Collections::Generic::IList<Material^>^ mtr );
	};
}