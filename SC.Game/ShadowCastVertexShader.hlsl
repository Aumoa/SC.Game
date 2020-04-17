#include "RenderingShaderCommon.hlsli"

struct Fragment
{
	float4 PosH : SV_Position;
};

Fragment main( Vertex vIn )
{
	Fragment fg;

	fg.PosH = mul( float4( vIn.Pos, 1.0f ), mul( gTransform.World, gLight.ViewProj ) );

	return fg;
}