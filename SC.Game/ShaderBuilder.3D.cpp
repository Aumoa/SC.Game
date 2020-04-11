using namespace SC;
using namespace SC::Game;

#pragma unmanaged

#include "CompiledShader/ColorVertexShader"
#include "CompiledShader/ColorPixelShader"

ComPtr<ID3D12RootSignature> ShaderBuilder::pRootSignature3D;
ComPtr<ID3D12PipelineState> ShaderBuilder::pPipelineStateColor;

void ShaderBuilder::Load3DShader()
{
	auto pDevice = Graphics::mDevice->pDevice.Get();

	D3D12_DESCRIPTOR_RANGE textures[]
	{
		{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 3, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND }
	};

	CRootSignatureDesc rootSignatureDesc;
	rootSignatureDesc.InputAssemblerInputLayout = true;
	rootSignatureDesc.VertexShaderRootAccess = true;
	rootSignatureDesc.PixelShaderRootAccess = true;

	rootSignatureDesc.AddConstantBufferView( 0 ); /* gCamera */
	rootSignatureDesc.AddConstantBufferView( 1, D3D12_SHADER_VISIBILITY_VERTEX ); /* gTransform */
	rootSignatureDesc.AddConstantBufferView( 2 ); /* gLight */
	rootSignatureDesc.AddConstantBufferView( 3 ); /* gMaterial */

	rootSignatureDesc.AddDescriptorTable( textures );

	rootSignatureDesc.AddStaticSampler( D3D12_FILTER_ANISOTROPIC, D3D12_TEXTURE_ADDRESS_MODE_BORDER, 8 );

	ComPtr<ID3DBlob> pRSBlob;
	HR( D3D12SerializeRootSignature( rootSignatureDesc.Get(), D3D_ROOT_SIGNATURE_VERSION_1_0, &pRSBlob, nullptr ) );
	HR( pDevice->CreateRootSignature( 0, pRSBlob->GetBufferPointer(), pRSBlob->GetBufferSize(), IID_PPV_ARGS( &pRootSignature3D ) ) );

	CGraphicsPipelineStateDesc pipelineDesc( pRootSignature3D.Get() );
	pipelineDesc.RTVCount = 3;
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipelineDesc.RTVFormats[1] = DXGI_FORMAT_R11G11B10_FLOAT;
	pipelineDesc.RTVFormats[2] = DXGI_FORMAT_R16_UINT;
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	pipelineDesc.SetVertexShader( pColorVertexShader, ARRAYSIZE( pColorVertexShader ) );
	pipelineDesc.SetPixelShader( pColorPixelShader, ARRAYSIZE( pColorPixelShader ) );
	pipelineDesc.AddInputLayout( Vertex::InputElements );
	pipelineDesc.SetDepthStencilState( true );
	pipelineDesc.CullMode = D3D12_CULL_MODE_NONE;
	//pipelineDesc.WireframeMode = true;
	pipelineDesc.SetBlendState( 0, true, D3D12_BLEND_SRC_ALPHA, D3D12_BLEND_INV_SRC_ALPHA, D3D12_BLEND_OP_ADD );
	HR( pDevice->CreateGraphicsPipelineState( pipelineDesc.Get(), IID_PPV_ARGS( &pPipelineStateColor ) ) );
}