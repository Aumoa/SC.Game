using namespace SC;
using namespace SC::Game;

#pragma unmanaged

#include "CompiledShader/UIVertexShader"
#include "CompiledShader/UIPixelShader"

ComPtr<ID3D12RootSignature> ShaderBuilder::pRootSignatureUI;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateUI;

void ShaderBuilder::LoadUIShader()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_DESCRIPTOR_RANGE textBuffer[]
	{
		{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND }
	};

	CRootSignatureDesc rootSignatureDesc;
	rootSignatureDesc.InputAssemblerInputLayout = true;
	rootSignatureDesc.VertexShaderRootAccess = true;
	rootSignatureDesc.PixelShaderRootAccess = true;

	rootSignatureDesc.AddConstantBufferView( 0 );
	rootSignatureDesc.AddRoot32BitConstants( 1, 2, D3D12_SHADER_VISIBILITY_PIXEL );
	rootSignatureDesc.AddShaderResourceView( 0, D3D12_SHADER_VISIBILITY_VERTEX );
	rootSignatureDesc.AddDescriptorTable( textBuffer, D3D12_SHADER_VISIBILITY_PIXEL );
	rootSignatureDesc.AddConstantBufferView( 2, D3D12_SHADER_VISIBILITY_PIXEL );
	rootSignatureDesc.AddRoot32BitConstants( 3, 2, D3D12_SHADER_VISIBILITY_PIXEL );

	rootSignatureDesc.AddStaticSampler( D3D12_FILTER_MIN_MAG_MIP_LINEAR, D3D12_TEXTURE_ADDRESS_MODE_BORDER );
	rootSignatureDesc.AddStaticSampler( D3D12_FILTER_MIN_MAG_MIP_POINT, D3D12_TEXTURE_ADDRESS_MODE_BORDER, 0, 1 );

	ComPtr<ID3DBlob> pRSBlob;
	HR( D3D12SerializeRootSignature( rootSignatureDesc.Get(), D3D_ROOT_SIGNATURE_VERSION_1_0, &pRSBlob, nullptr ) );
	HR( pDevice->CreateRootSignature( 0, pRSBlob->GetBufferPointer(), pRSBlob->GetBufferSize(), IID_PPV_ARGS( &pRootSignatureUI ) ) );

	CGraphicsPipelineStateDesc pipelineDesc( pRootSignatureUI.Get() );
	pipelineDesc.RTVCount = 1;
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineDesc.SetVertexShader( pUIVertexShader, ARRAYSIZE( pUIVertexShader ) );
	pipelineDesc.SetPixelShader( pUIPixelShader, ARRAYSIZE( pUIPixelShader ) );
	pipelineDesc.SetBlendState( 0, true, D3D12_BLEND_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA );
	HR( pDevice->CreateGraphicsPipelineState( pipelineDesc.Get(), IID_PPV_ARGS( &pPipelineStateUI ) ) );
}