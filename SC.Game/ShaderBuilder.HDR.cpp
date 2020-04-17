using namespace SC;
using namespace SC::Game;

#pragma unmanaged

#include "CompiledShader/HDRVertexShader"
#include "CompiledShader/HDRLightShader"
#include "CompiledShader/HDRColorShader"

ComPtr<ID3D12RootSignature> ShaderBuilder::pRootSignatureHDR;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateLighting;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateHDRColor;

void ShaderBuilder::LoadHDRShader()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_DESCRIPTOR_RANGE hdrSource0[]
	{
		{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 4, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
	};

	D3D12_DESCRIPTOR_RANGE shadowDepth[]
	{
		{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 5, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND }
	};

	CRootSignatureDesc rootSignatureDesc;
	rootSignatureDesc.PixelShaderRootAccess = true;

	rootSignatureDesc.AddConstantBufferView( 0 );
	rootSignatureDesc.AddDescriptorTable( hdrSource0 );
	rootSignatureDesc.AddConstantBufferView( 1 );
	rootSignatureDesc.AddShaderResourceView( 4 );
	rootSignatureDesc.AddDescriptorTable( shadowDepth );

	rootSignatureDesc.AddStaticSampler( D3D12_FILTER_MIN_MAG_MIP_POINT, D3D12_TEXTURE_ADDRESS_MODE_BORDER );
	rootSignatureDesc.AddStaticComparisonSampler( D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR, D3D12_TEXTURE_ADDRESS_MODE_BORDER, 1 );

	ComPtr<ID3DBlob> pRSBlob;
	HR( D3D12SerializeRootSignature( rootSignatureDesc.Get(), D3D_ROOT_SIGNATURE_VERSION_1_0, &pRSBlob, nullptr ) );
	HR( pDevice->CreateRootSignature( 0, pRSBlob->GetBufferPointer(), pRSBlob->GetBufferSize(), IID_PPV_ARGS( &pRootSignatureHDR ) ) );

	CGraphicsPipelineStateDesc pipelineDesc( pRootSignatureHDR );
	pipelineDesc.RTVCount = 1;
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
	pipelineDesc.SetVertexShader( pHDRVertexShader, ARRAYSIZE( pHDRVertexShader ) );
	pipelineDesc.SetPixelShader( pHDRLightShader, ARRAYSIZE( pHDRLightShader ) );
	pipelineDesc.SetBlendState( 0, true, D3D12_BLEND_INV_DEST_ALPHA, D3D12_BLEND_ONE, D3D12_BLEND_OP_ADD );
	HR( pDevice->CreateGraphicsPipelineState( pipelineDesc.Get(), IID_PPV_ARGS( &pPipelineStateLighting ) ) );

	pipelineDesc.SetPixelShader( pHDRColorShader, ARRAYSIZE( pHDRColorShader ) );
	pipelineDesc.SetBlendState( 0, true, D3D12_BLEND_DEST_COLOR, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD, D3D12_BLEND_ZERO, D3D12_BLEND_ONE );
	HR( pDevice->CreateGraphicsPipelineState( pipelineDesc.Get(), IID_PPV_ARGS( &pPipelineStateHDRColor ) ) );
}