#pragma once

namespace SC::Game
{
	constexpr int Slot_UI_ScreenResolution = 0;
	constexpr int Slot_UI_CursorPos = 1;
	constexpr int Slot_UI_ShaderInfo = 2;
	constexpr int Slot_UI_Image = 3;
	constexpr int Slot_UI_Brush = 4;
	constexpr int Slot_UI_RenderType = 5;

	class ShaderBuilder
	{
	public:
		static ComPtr<ID3D12RootSignature> pRootSignatureUI;
		static ComPtr<ID3D12PipelineState> pPipelineStateUI;

	public:
		static void Initialize();

	private:
		static void OnDisposing();
		static void LoadUIShader();
	};
}