#include "HDR.hlsli"
#include "GammaHelper.hlsli"

struct Fragment
{
	float4 PosH : SV_Position;
	float2 Tex : TEXCOORD;
};

struct Pixel
{
	float4 Color : SV_Target0;
};

Texture2D<float4> gHDRSource : register( t0 );
SamplerState gSampler : register( s0 );
ConstantBuffer<HDRConstants> gHDRConstants : register( b0 );

float3 ToneMapping( float3 Color, float AvgLum )
{
	float MiddleGrey = AvgLum;
	float LumWhiteSqr = AvgLum;

	float LScale = CalcLum( Color.xyz );
	LScale *= MiddleGrey / AvgLum;
	LScale = ( LScale + LScale * LScale / LumWhiteSqr ) / ( 1.0f + LScale );

	Color.xyz = Color.xyz * LScale;
	Color = pow( Color, 1.0f / 2.2f );
	return float3( Color );
}
Pixel main( Fragment pIn )
{
	Pixel px;

	px.Color = gHDRSource.Sample( gSampler, pIn.Tex );
	if ( px.Color.w < 0.5f )
		px.Color.xyz = ToneMapping( px.Color.xyz, gHDRConstants.AverageLum );
	
	return px;
}