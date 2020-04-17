using namespace SC;
using namespace SC::Game;

#pragma unmanaged

#include "CompiledShader/SkinningComputeShader"

ComPtr<ID3D12RootSignature> ShaderBuilder::pRootSignature_Skinning;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineState_Skinning;

void ShaderBuilder::LoadSkinningShader()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	CRootSignatureDesc rootSignatureDesc;
	rootSignatureDesc.AddShaderResourceView( 0 );
	rootSignatureDesc.AddShaderResourceView( 1 );
	rootSignatureDesc.AddUnorderedAccessView( 0 );
	rootSignatureDesc.AddRoot32BitConstants( 0, 1 );

	ComPtr<ID3DBlob> pRSBlob;
	HR( D3D12SerializeRootSignature( rootSignatureDesc.Get(), D3D_ROOT_SIGNATURE_VERSION_1_0, &pRSBlob, nullptr ) );
	HR( pDevice->CreateRootSignature( 0, pRSBlob->GetBufferPointer(), pRSBlob->GetBufferSize(), IID_PPV_ARGS( &pRootSignature_Skinning ) ) );

	D3D12_COMPUTE_PIPELINE_STATE_DESC pipelineDesc{ };
	pipelineDesc.pRootSignature = pRootSignature_Skinning.Get();
	pipelineDesc.CS = { pSkinningComputeShader, ARRAYSIZE( pSkinningComputeShader ) };
	HR( pDevice->CreateComputePipelineState( &pipelineDesc, IID_PPV_ARGS( &pPipelineState_Skinning ) ) );
}