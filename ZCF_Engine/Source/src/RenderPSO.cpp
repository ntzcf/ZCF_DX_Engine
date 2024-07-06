#include "Render/RenderPSO.h"

namespace Engine::Render::resource 
{


	D3D12_INPUT_ELEMENT_DESC CreateInputDESC(InputElementView InputView)
	{
		D3D12_INPUT_ELEMENT_DESC InputDesc;
		InputDesc.SemanticName = InputView.SemanticName;
		InputDesc.SemanticIndex = InputView.SemanticIndex;
		
		InputDesc.InputSlot = InputView.InputSlot;

		InputDesc.Format = InputView.Format;
		
		InputDesc.AlignedByteOffset = InputView.AlignedByteOffset;

		InputDesc.InputSlotClass = InputView.IsInstance ? 
			D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA : D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		InputDesc.InstanceDataStepRate = InputView.InstanceDataStepRate;
	
		return InputDesc;
	}

	D3D12_RASTERIZER_DESC CreateDefaultRasterDESC(Rasterize Rasterize) 
	{
		D3D12_RASTERIZER_DESC  RasterizeDesc;
		RasterizeDesc.FillMode = Rasterize.FillMode == Solid ? D3D12_FILL_MODE_SOLID : D3D12_FILL_MODE_WIREFRAME;
		RasterizeDesc.CullMode = Rasterize.CullMode == Front ? D3D12_CULL_MODE_FRONT : D3D12_CULL_MODE_BACK;
		RasterizeDesc.FrontCounterClockwise = Rasterize.FrontCounterClockwise;
		RasterizeDesc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		RasterizeDesc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		RasterizeDesc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		RasterizeDesc.DepthClipEnable = TRUE;
		RasterizeDesc.MultisampleEnable = FALSE;
		RasterizeDesc.AntialiasedLineEnable = FALSE;
		RasterizeDesc.ForcedSampleCount = 0;
		RasterizeDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	}
	D3D12_BLEND_DESC      CreateDefaultOpacityBlendState()
	{
		D3D12_BLEND_DESC  BlendDesc;
		BlendDesc.AlphaToCoverageEnable = FALSE;
		BlendDesc.IndependentBlendEnable = FALSE;
		const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
		{
			FALSE,FALSE,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP,
			D3D12_COLOR_WRITE_ENABLE_ALL,
		};
		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
			BlendDesc.RenderTarget[i] = defaultRenderTargetBlendDesc;
	}
	D3D12_DEPTH_STENCIL_DESC  CreateDefaultD_S_State()
	{
		D3D12_DEPTH_STENCIL_DESC  D_S_State;
		D_S_State.DepthEnable = TRUE;
		D_S_State.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		D_S_State.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		D_S_State.StencilEnable = FALSE;
		D_S_State.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
		D_S_State.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
		const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp =
		{ D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
		D_S_State.FrontFace = defaultStencilOp;
		D_S_State.BackFace = defaultStencilOp;
	}





}