#pragma once

namespace SC::Game
{
#pragma pack( push, 4 )
	struct Vertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
		XMFLOAT2 Tex;
		XMFLOAT3 Normal;
		XMFLOAT3 Tangent;

		Vertex()
		{

		}

		Vertex( FXMVECTOR pos, FXMVECTOR normal, FXMVECTOR tex )
		{
			XMStoreFloat3( &Pos, pos );
			Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			XMStoreFloat3( &Normal, normal );
			XMStoreFloat2( &Tex, tex );
			Tangent = {  };
		}

		bool operator==( const Vertex& copy ) const
		{
			return memcmp( this, &copy, sizeof( Vertex ) ) == 0;
		}

		inline static D3D12_INPUT_ELEMENT_DESC InputElements[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA },
			{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 48, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA }
		};
	};

	struct SkinnedVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
		XMFLOAT2 Tex;
		XMFLOAT3 Normal;
		XMFLOAT3 Tangent;
		float Weights[3];
		unsigned short Indices[4];

		bool operator==( const Vertex& copy ) const
		{
			return memcmp( this, &copy, sizeof( SkinnedVertex ) ) == 0;
		}
	};
#pragma pack( pop )
}