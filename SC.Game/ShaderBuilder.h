#pragma once

namespace SC::Game
{
	constexpr int Slot_UI_ScreenResolution = 0;
	constexpr int Slot_UI_CursorPos = 1;
	constexpr int Slot_UI_ShaderInfo = 2;
	constexpr int Slot_UI_Image = 3;
	constexpr int Slot_UI_Brush = 4;
	constexpr int Slot_UI_RenderType = 5;

	constexpr int Slot_3D_Camera = 0;
	constexpr int Slot_3D_Transform = 1;
	constexpr int Slot_3D_Light = 2;
	constexpr int Slot_3D_Material = 3;
	constexpr int Slot_3D_Textures = 4;

	constexpr int Slot_PP_HDRBuffer = 0;
	constexpr int Slot_PP_HDRConstants = 1;

	class ShaderBuilder
	{
	public:
		static ComPtr<ID3D12RootSignature> pRootSignatureUI;
		static ComPtr<ID3D12PipelineState> pPipelineStateUI;

		static ComPtr<ID3D12RootSignature> pRootSignature3D;
		static ComPtr<ID3D12PipelineState> pPipelineStateColor;

		static ComPtr<ID3D12RootSignature> pRootSignaturePP;
		static ComPtr<ID3D12PipelineState> pPipelineStateToneMapping;

	public:
		static void Initialize();

	private:
		static void OnDisposing();
		static void LoadUIShader();
		static void Load3DShader();
		static void LoadPostProcessShader();
	};
}