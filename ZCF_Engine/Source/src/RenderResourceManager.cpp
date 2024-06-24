#include "Render/RenderResourceManager.h"
#include "Render/SrcRenderHelper.h"

namespace Engine::Render::resource
{

	void RenderResourceManager::Update()
	{
		DW.Update();
		m_commandAllocator	=	DW.GetCommandAllocator();
		m_renderTarget		=	DW.GetRenderTarget();
		m_frameIndex		=	DW.GetCurrentFrameIndex();


	}

	void RenderResourceManager::Init(HWND window, int width, int height)
	{
		DW.Init(window, width, height);

		m_device			=	DW.GetD3DDevice();
		m_commandQueue		=	DW.GetCommandQueue();

		DW.Update();

		m_commandAllocator	=	DW.GetCommandAllocator();
		m_renderTarget		=	DW.GetRenderTarget();
		m_frameIndex		=	DW.GetCurrentFrameIndex();


		m_viewPort = { 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
		m_scissorRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };

		/*CreateRootSignature();
		CreatePSO();
		CreateCmdList();
		CreateFenceAndEvent();
		CreateBarrier();
		CreateVertexBuffer();*/
	}


	void RenderResourceManager::CreateRootSignature()
	{
		// 创建空根签名。
		{
			D3D12_ROOT_SIGNATURE_DESC	descRootSignature =
			{
				0
				, nullptr
				, 0
				, nullptr
				, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
			};
			std::string Trangle = "Trangle";
			RootSignatures.emplace(std::move(Trangle), std::move(descRootSignature));
			ComPtr<ID3DBlob> pSignature;
			ComPtr<ID3DBlob> pError;
			ThrowIfFailed(D3D12SerializeRootSignature(&descRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, pSignature.GetAddressOf(), pError.GetAddressOf()));
			ThrowIfFailed(m_device->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
			NAME_D3D12_OBJECT(m_rootSignature);
		}
	}
	void RenderResourceManager::CreatePSO()
	{
		CreateRootSignature();

#if defined(_DEBUG)
		//调试状态下，打开Shader编译的调试标志，不优化
		UINT nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT nCompileFlags = 0;
#endif
		TCHAR	AppPath[MAX_PATH] = {};
		StringCchPrintf(ShaderPath
			, MAX_PATH
			, _T("E:\\My projects\\DX12_Engine\\ZCF_Engine\\Shaders\\shader1.hlsl")
			, AppPath);
		const char* version= "ps_5_0";
		std::string version1 = "vs_5_0";
		auto version2 = version1.c_str();
		ThrowIfFailed(D3DCompileFromFile(ShaderPath
			, nullptr
			, nullptr
			, "VSMain"
			, version2
			, nCompileFlags
			, 0
			, &m_vertexShader
			, nullptr));
		ThrowIfFailed(D3DCompileFromFile(ShaderPath
			, nullptr
			, nullptr
			, "PSMain"
			, version//"ps_5_0"
			, nCompileFlags
			, 0
			, &m_pixelShader
			, nullptr));

		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC stInputElementDescs[] =
		{
			{
				"POSITION"
				, 0
				, DXGI_FORMAT_R32G32B32A32_FLOAT
				, 0
				, 0
				, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA
				, 0
			},
			{
				"COLOR"
				, 0
				, DXGI_FORMAT_R32G32B32A32_FLOAT
				, 0
				, 16
				, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA
				, 0
			}
		};

		// 定义渲染管线状态描述结构，创建渲染管线对象
		D3D12_GRAPHICS_PIPELINE_STATE_DESC stPSODesc = {};
		stPSODesc.InputLayout = { stInputElementDescs, _countof(stInputElementDescs) };
		stPSODesc.pRootSignature = m_rootSignature.Get();
		stPSODesc.VS.pShaderBytecode = m_vertexShader->GetBufferPointer();
		stPSODesc.VS.BytecodeLength = m_vertexShader->GetBufferSize();
		stPSODesc.PS.pShaderBytecode = m_pixelShader->GetBufferPointer();
		stPSODesc.PS.BytecodeLength = m_pixelShader->GetBufferSize();

		stPSODesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		stPSODesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;

		stPSODesc.BlendState.AlphaToCoverageEnable = FALSE;
		stPSODesc.BlendState.IndependentBlendEnable = FALSE;
		stPSODesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		stPSODesc.DepthStencilState.DepthEnable = FALSE;
		stPSODesc.DepthStencilState.StencilEnable = FALSE;

		stPSODesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		stPSODesc.NumRenderTargets = 1;
		stPSODesc.RTVFormats[0] = DW.GetBackBufferFormat();

		stPSODesc.SampleMask = UINT_MAX;
		stPSODesc.SampleDesc.Count = 1;

		ThrowIfFailed(m_device->CreateGraphicsPipelineState(&stPSODesc, IID_PPV_ARGS(&m_pipelineState)));

	}
	void RenderResourceManager::CreateCmdList()
	{
		ThrowIfFailed(m_device->CreateCommandList(
			0
			, D3D12_COMMAND_LIST_TYPE_DIRECT
			, m_commandAllocator.Get()
			, m_pipelineState.Get()
			, IID_PPV_ARGS(&m_commandList)));

		m_commandList->Close();
	}
	void RenderResourceManager::CreateVertexBuffer()
	{
		struct VERTEX
		{
			XMFLOAT4 m_vtPos;
			XMFLOAT4 m_vtColor;
		};

		float								fTrangleSize = 3.0f;

		VERTEX TriangleVertices[] =
		{
			{ { 0.0f, 0.25f * fTrangleSize, 0.0f ,1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 0.25f * fTrangleSize, -0.25f * fTrangleSize, 0.0f ,1.0f  }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.25f * fTrangleSize, -0.25f * fTrangleSize, 0.0f  ,1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
		};

		const UINT VertexBufferSize = sizeof(TriangleVertices);


		D3D12_HEAP_PROPERTIES stHeapProp = { D3D12_HEAP_TYPE_UPLOAD };

		D3D12_RESOURCE_DESC stResSesc = {};
		stResSesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		stResSesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		stResSesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		stResSesc.Format = DXGI_FORMAT_UNKNOWN;
		stResSesc.Width = VertexBufferSize;
		stResSesc.Height = 1;
		stResSesc.DepthOrArraySize = 1;
		stResSesc.MipLevels = 1;
		stResSesc.SampleDesc.Count = 1;
		stResSesc.SampleDesc.Quality = 0;

		ThrowIfFailed(m_device->CreateCommittedResource(
			&stHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&stResSesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer)));

		UINT8* pVertexDataBegin = nullptr;
		D3D12_RANGE stReadRange = { 0, 0 };
		ThrowIfFailed(m_vertexBuffer->Map(
			0
			, &stReadRange
			, reinterpret_cast<void**>(&pVertexDataBegin)));

		memcpy(pVertexDataBegin
			, TriangleVertices
			, sizeof(TriangleVertices));

		m_vertexBuffer->Unmap(0, nullptr);

		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.StrideInBytes = sizeof(VERTEX);
		m_vertexBufferView.SizeInBytes = VertexBufferSize;
	}
	void RenderResourceManager::CreateFenceAndEvent()
	{
		ThrowIfFailed(m_device->CreateFence(m_fenceValues[m_frameIndex], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		m_fenceValues[m_frameIndex]++;

		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (m_fenceEvent == nullptr)
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}
	}
	void RenderResourceManager::CreateBarrier()
	{
		m_beginResBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		m_beginResBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_beginResBarrier.Transition.pResource = m_renderTarget.Get();
		m_beginResBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		m_beginResBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		m_beginResBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		
		m_endResBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		m_endResBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_endResBarrier.Transition.pResource = m_renderTarget.Get();
		m_endResBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		m_endResBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		m_endResBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	}
	void RenderResourceManager::run()
	{
		/*m_commandList->Close();*/
		////命令分配器先Reset一下
		//ThrowIfFailed(m_commandAllocator->Reset());
		//m_commandList->Close();
		////Reset命令列表，并重新指定命令分配器和PSO对象
		//ThrowIfFailed(m_commandList->Reset(m_commandAllocator.Get(), m_pipelineState.Get()));

		////开始记录命令
		//m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());
		//m_commandList->SetPipelineState(m_pipelineState.Get());
		//m_commandList->RSSetViewports(1, &m_viewPort);
		//m_commandList->RSSetScissorRects(1, &m_scissorRect);

		//// 通过资源屏障判定后缓冲已经切换完毕可以开始渲染了
		//m_beginResBarrier.Transition.pResource = m_renderTarget.Get();
		//m_commandList->ResourceBarrier(1, &m_beginResBarrier);

		////设置渲染目标
		//D3D12_CPU_DESCRIPTOR_HANDLE rtvhandle= DW.GetRenderTargetView();
		//m_commandList->OMSetRenderTargets(1, &rtvhandle, FALSE, nullptr);

		//// 继续记录命令，并真正开始新一帧的渲染
		//const float							faClearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
		//m_commandList->ClearRenderTargetView(DW.GetRenderTargetView(), faClearColor, 0, nullptr);
		//m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);

		////Draw Call！！！
		//m_commandList->DrawInstanced(3, 1, 0, 0);

		////又一个资源屏障，用于确定渲染已经结束可以提交画面去显示了
		//m_endResBarrier.Transition.pResource = m_renderTarget.Get();
		//m_commandList->ResourceBarrier(1, &m_endResBarrier);
		////关闭命令列表，可以去执行了
		//ThrowIfFailed(m_commandList->Close());

		////执行命令列表
		//ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
		//m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		////提交画面
		//ThrowIfFailed(DW.GetSwapChain()->Present(1, 0));

		////开始同步GPU与CPU的执行，先记录围栏标记值
		//const UINT64 n64CurrentFenceValue = m_fenceValues[m_frameIndex];
		//ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), n64CurrentFenceValue));
		//m_fenceValues[m_frameIndex]++;
		//ThrowIfFailed(m_fence->SetEventOnCompletion(n64CurrentFenceValue, m_fenceEvent));
	}

	void RenderResourceManager::CreatePassResource(Engine::Render::renderpass::RenderPassInfo PPI)
	{
		CreatePSO();
		CreateBuffer();
	}

	/// <summary>
	/// ////////////////////////////////CreatePassResource//////////////////////////////////////////
	/// </summary>
	/// <param name="LPI"></param>
	void RenderResourceManager::CreateLearnPassResource(Engine::Render::renderpass::LearnPassInfo LPI)
	{
		//
		CreatePSO();
		CreateVertexBuffer();
		CreateIndexBuffer();
	}
};