using namespace SC;
using namespace SC::Game;

#pragma unmanaged

#include "CompiledShader/HDRSamplingComputeShader"
#include "CompiledShader/HDRLumCompressComputeShader"
#include "CompiledShader/HDRAverageLumComputeShader"

ComPtr<ID3D12RootSignature> ShaderBuilder::pRootSignatureHDRCompute;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateSamplingCompute;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateLumCompressCompute;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateAverageLumCompute;

void ShaderBuilder::LoadHDRComputeShader()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_DESCRIPTOR_RANGE hdrBuffer[]
	{
		{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND }
	};

	D3D12_DESCRIPTOR_RANGE halfHDRAndConstants[]
	{
		{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 2, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND }
	};

	CRootSignatureDesc rootSignatureDesc;
	rootSignatureDesc.AddDescriptorTable( hdrBuffer );
	rootSignatureDesc.AddDescriptorTable( halfHDRAndConstants );
	rootSignatureDesc.AddRoot32BitConstants( 0, 1 );

	ComPtr<ID3DBlob> pRSBlob;
	HR( D3D12SerializeRootSignature( rootSignatureDesc.Get(), D3D_ROOT_SIGNATURE_VERSION_1_0, &pRSBlob, nullptr ) );
	HR( pDevice->CreateRootSignature( 0, pRSBlob->GetBufferPointer(), pRSBlob->GetBufferSize(), IID_PPV_ARGS( &pRootSignatureHDRCompute ) ) );

	D3D12_COMPUTE_PIPELINE_STATE_DESC pipelineDesc{ };
	pipelineDesc.pRootSignature = pRootSignatureHDRCompute.Get();
	pipelineDesc.CS = { pHDRSamplingComputeShader, ARRAYSIZE( pHDRSamplingComputeShader ) };
	HR( pDevice->CreateComputePipelineState( &pipelineDesc, IID_PPV_ARGS( &pPipelineStateSamplingCompute ) ) );

	pipelineDesc.CS = { pHDRLumCompressComputeShader, ARRAYSIZE( pHDRLumCompressComputeShader ) };
	HR( pDevice->CreateComputePipelineState( &pipelineDesc, IID_PPV_ARGS( &pPipelineStateLumCompressCompute ) ) );

	pipelineDesc.CS = { pHDRAverageLumComputeShader, ARRAYSIZE( pHDRAverageLumComputeShader ) };
	HR( pDevice->CreateComputePipelineState( &pipelineDesc, IID_PPV_ARGS( &pPipelineStateAverageLumCompute ) ) );
}