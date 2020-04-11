#pragma unmanaged

using namespace SC;
using namespace SC::Game;

void ShaderBuilder::Initialize()
{
	App::Disposing.push_front( OnDisposing );

	LoadUIShader();
	Load3DShader();
	LoadPostProcessShader();
}

void ShaderBuilder::OnDisposing()
{
	pRootSignatureUI.Reset();
	pPipelineStateUI.Reset();

	pRootSignature3D.Reset();
	pPipelineStateColor.Reset();

	pRootSignaturePP.Reset();
	pPipelineStateToneMapping.Reset();
}