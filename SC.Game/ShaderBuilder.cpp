#pragma unmanaged

using namespace SC;
using namespace SC::Game;

void ShaderBuilder::Initialize()
{
	App::Disposing.push_front( OnDisposing );

	LoadUIShader();
	LoadSkinningShader();
	Load3DShader();
	LoadHDRShader();
	LoadHDRComputeShader();
	LoadPostProcessShader();
}

void ShaderBuilder::OnDisposing()
{
	pRootSignatureUI.Reset();
	pPipelineStateUI.Reset();

	pRootSignature3D.Reset();
	pPipelineStateColor.Reset();

	pRootSignatureHDR.Reset();
	pPipelineStateLighting.Reset();
	pPipelineStateHDRColor.Reset();

	pRootSignatureHDRCompute.Reset();
	pPipelineStateSamplingCompute.Reset();
	pPipelineStateLumCompressCompute.Reset();
	pPipelineStateAverageLumCompute.Reset();

	pRootSignaturePP.Reset();
	pPipelineStateToneMapping.Reset();
}