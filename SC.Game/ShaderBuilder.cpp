#pragma unmanaged

using namespace SC;
using namespace SC::Game;

void ShaderBuilder::Initialize()
{
	App::Disposing.push_front( OnDisposing );

	LoadUIShader();
}

void ShaderBuilder::OnDisposing()
{
	pRootSignatureUI.Reset();
	pPipelineStateUI.Reset();
}