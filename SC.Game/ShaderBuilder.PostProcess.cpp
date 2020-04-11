using namespace SC;
using namespace SC::Game;

#pragma unmanaged

#include "CompiledShader/ToneMappingVertexShader"
#include "CompiledShader/ToneMappingPixelShader"

ComPtr<ID3D12RootSignature> ShaderBuilder::pRootSignaturePP;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateToneMapping;

void ShaderBuilder::LoadPostProcessShader()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_DESCRIPTOR_RANGE hdrSource[]
	{
		{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND }
	};

	CRootSignatureDesc rootSignatureDesc;
	rootSignatureDesc.PixelShaderRootAccess = true;
	rootSignatureDesc.AddDescriptorTable( hdrSource );
	rootSignatureDesc.AddConstantBufferView( 0 );
	rootSignatureDesc.AddStaticSampler( D3D12_FILTER_MIN_MAG_MIP_LINEAR, D3D12_TEXTURE_ADDRESS_MODE_BORDER );

	ComPtr<ID3DBlob> pRSBlob;
	HR( D3D12SerializeRootSignature( rootSignatureDesc.Get(), D3D_ROOT_SIGNATURE_VERSION_1_0, &pRSBlob, nullptr ) );
	HR( pDevice->CreateRootSignature( 0, pRSBlob->GetBufferPointer(), pRSBlob->GetBufferSize(), IID_PPV_ARGS( &pRootSignaturePP ) ) );

	CGraphicsPipelineStateDesc pipelineDesc( pRootSignaturePP );
	pipelineDesc.RTVCount = 1;
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineDesc.SetVertexShader( pToneMappingVertexShader, ARRAYSIZE( pToneMappingVertexShader ) );
	pipelineDesc.SetPixelShader( pToneMappingPixelShader, ARRAYSIZE( pToneMappingPixelShader ) );
	HR( pDevice->CreateGraphicsPipelineState( pipelineDesc.Get(), IID_PPV_ARGS( &pPipelineStateToneMapping ) ) );
}