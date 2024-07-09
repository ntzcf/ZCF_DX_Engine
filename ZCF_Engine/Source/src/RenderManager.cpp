#include "Render/RenderManager.h"
#include <minwinbase.h>

using namespace Engine::Render::renderpass;
using namespace Engine::Render::resource;

namespace Engine::Render::resource
{
	void RenderResourceManager::Init(HWND window, int width, int height)
	{
		DW.Init(window, width, height);

		m_device = DW.GetD3DDevice();
		m_commandQueue = DW.GetCommandQueue();


		SRV_CBV_UAV_Descriptor_size = m_device.Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		Sampler_Descriptor_size = m_device.Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
		m_commandAllocator = DW.GetCommandAllocator();
		m_renderTarget = DW.GetRenderTarget();
		m_frameIndex = DW.GetCurrentFrameIndex();

		//提前编译 , 或者加载已编译好的Shader ,以及的缓存PSO
		mShaders.emplace("DepthPassVS", new ComPtr<ID3DBlob>);
		mShaders.emplace("DepthPassPS", new ComPtr<ID3DBlob>);
		
		mShaders["DepthPassVS"] = d3dUtil::CompileShader(
			L"E:\\My projects\\DX12_Engine\\ZCF_Engine\\ZCF_Engine\\Source\\shaders\\DepthPass.hlsl",
			nullptr, "VS", "vs_5_0");

		mShaders["DepthPassPS"] = d3dUtil::CompileShader(
			L"E:\\My projects\\DX12_Engine\\ZCF_Engine\\ZCF_Engine\\Source\\shaders\\DepthPass.hlsl",
			nullptr, "PS", "ps_5_0");

	}

	void RenderResourceManager::Update()
	{
		DW.Update();
		m_commandAllocator = DW.GetCommandAllocator();
		m_renderTarget = DW.GetRenderTarget();
		m_frameIndex = DW.GetCurrentFrameIndex();


	}


	//	void RenderResourceManager::CreateRootSignature()
	//	{
	//		// 创建空根签名。
	//		{
	//			D3D12_ROOT_SIGNATURE_DESC	descRootSignature =
	//			{
	//				0
	//				, nullptr
	//				, 0
	//				, nullptr
	//				, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
	//			};
	//			std::string Trangle = "Trangle";
	//			RootSignatures.emplace(std::move(Trangle), std::move(descRootSignature));
	//			ComPtr<ID3DBlob> pSignature;
	//			ComPtr<ID3DBlob> pError;
	//			ThrowIfFailed(D3D12SerializeRootSignature(&descRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, pSignature.GetAddressOf(), pError.GetAddressOf()));
	//			ThrowIfFailed(m_device->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
	//			NAME_D3D12_OBJECT(m_rootSignature);
	//		}
	//	}
	//	void RenderResourceManager::CreatePSO(renderpass::RenderPassInfo)
	//	{
	//		CreateRootSignature();
	//
	//#if defined(_DEBUG)
	//		//调试状态下，打开Shader编译的调试标志，不优化
	//		UINT nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	//#else
	//		UINT nCompileFlags = 0;
	//#endif
	//		TCHAR	AppPath[MAX_PATH] = {};
	//		StringCchPrintf(ShaderPath
	//			, MAX_PATH
	//			, _T("E:\\My projects\\DX12_Engine\\ZCF_Engine\\Shaders\\shader1.hlsl")
	//			, AppPath);
	//		const char* version= "ps_5_0";
	//		std::string version1 = "vs_5_0";
	//		auto version2 = version1.c_str();
	//		ThrowIfFailed(D3DCompileFromFile(ShaderPath
	//			, nullptr
	//			, nullptr
	//			, "VSMain"
	//			, version2
	//			, nCompileFlags
	//			, 0
	//			, &m_vertexShader
	//			, nullptr));
	//		ThrowIfFailed(D3DCompileFromFile(ShaderPath
	//			, nullptr
	//			, nullptr
	//			, "PSMain"
	//			, version//"ps_5_0"
	//			, nCompileFlags
	//			, 0
	//			, &m_pixelShader
	//			, nullptr));
	//
	//		// Define the vertex input layout.
	//		D3D12_INPUT_ELEMENT_DESC stInputElementDescs[] =
	//		{
	//			{
	//				"POSITION"
	//				, 0
	//				, DXGI_FORMAT_R32G32B32A32_FLOAT
	//				, 0
	//				, 0
	//				, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA
	//				, 0
	//			},
	//			{
	//				"COLOR"
	//				, 0
	//				, DXGI_FORMAT_R32G32B32A32_FLOAT
	//				, 0
	//				, 16
	//				, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA
	//				, 0
	//			}
	//		};
	//
	//		// 定义渲染管线状态描述结构，创建渲染管线对象
	//		D3D12_GRAPHICS_PIPELINE_STATE_DESC stPSODesc = {};
	//		stPSODesc.InputLayout = { stInputElementDescs, _countof(stInputElementDescs) };
	//		stPSODesc.pRootSignature = m_rootSignature.Get();
	//		stPSODesc.VS.pShaderBytecode = m_vertexShader->GetBufferPointer();
	//		stPSODesc.VS.BytecodeLength = m_vertexShader->GetBufferSize();
	//		stPSODesc.PS.pShaderBytecode = m_pixelShader->GetBufferPointer();
	//		stPSODesc.PS.BytecodeLength = m_pixelShader->GetBufferSize();
	//
	//		stPSODesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	//		stPSODesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
	//
	//		stPSODesc.BlendState.AlphaToCoverageEnable = FALSE;
	//		stPSODesc.BlendState.IndependentBlendEnable = FALSE;
	//		stPSODesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	//
	//		stPSODesc.DepthStencilState.DepthEnable = FALSE;
	//		stPSODesc.DepthStencilState.StencilEnable = FALSE;
	//
	//		stPSODesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//
	//		stPSODesc.NumRenderTargets = 1;
	//		stPSODesc.RTVFormats[0] = DW.GetBackBufferFormat();
	//
	//		stPSODesc.SampleMask = UINT_MAX;
	//		stPSODesc.SampleDesc.Count = 1;
	//
	//		ThrowIfFailed(m_device->CreateGraphicsPipelineState(&stPSODesc, IID_PPV_ARGS(&m_pipelineState)));
	//
	//	}
	//	void RenderResourceManager::CreateCmdList()
	//	{
	//		ThrowIfFailed(m_device->CreateCommandList(
	//			0
	//			, D3D12_COMMAND_LIST_TYPE_DIRECT
	//			, m_commandAllocator.Get()
	//			, m_pipelineState.Get()
	//			, IID_PPV_ARGS(&m_commandList)));
	//
	//		m_commandList->Close();
	//	}
	//	void RenderResourceManager::CreateBuffer()
	//	{
	//		ThrowIfFailed(m_device->CreateCommittedResource(
	//			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), // 堆的类型：Default
	//			D3D12_HEAP_FLAG_NONE,
	//			&CD3DX12_RESOURCE_DESC::Buffer(byteSize), // 资源的大小
	//			D3D12_RESOURCE_STATE_COMMON,  // 初始状态
	//			nullptr,
	//			IID_PPV_ARGS(defaultBuffer.GetAddressOf()))); // 创建的资源，通过引用参数方式传入. defualtBuffer类型为ComPtr<ID3DResource>
	//
	//	}
	//	void RenderResourceManager::CreateVertexBuffer()
	//	{
	//		struct VERTEX
	//		{
	//			XMFLOAT4 m_vtPos;
	//			XMFLOAT4 m_vtColor;
	//		};
	//
	//		float								fTrangleSize = 3.0f;
	//
	//		VERTEX TriangleVertices[] =
	//		{
	//			{ { 0.0f, 0.25f * fTrangleSize, 0.0f ,1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	//			{ { 0.25f * fTrangleSize, -0.25f * fTrangleSize, 0.0f ,1.0f  }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	//			{ { -0.25f * fTrangleSize, -0.25f * fTrangleSize, 0.0f  ,1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	//		};
	//
	//		const UINT VertexBufferSize = sizeof(TriangleVertices);
	//
	//
	//		D3D12_HEAP_PROPERTIES stHeapProp = { D3D12_HEAP_TYPE_UPLOAD };
	//
	//		D3D12_RESOURCE_DESC stResSesc = {};
	//		stResSesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	//		stResSesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//		stResSesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	//		stResSesc.Format = DXGI_FORMAT_UNKNOWN;
	//		stResSesc.Width = VertexBufferSize;
	//		stResSesc.Height = 1;
	//		stResSesc.DepthOrArraySize = 1;
	//		stResSesc.MipLevels = 1;
	//		stResSesc.SampleDesc.Count = 1;
	//		stResSesc.SampleDesc.Quality = 0;
	//
	//		ThrowIfFailed(m_device->CreateCommittedResource(
	//			&stHeapProp,
	//			D3D12_HEAP_FLAG_NONE,
	//			&stResSesc,
	//			D3D12_RESOURCE_STATE_GENERIC_READ,
	//			nullptr,
	//			IID_PPV_ARGS(&m_vertexBuffer)));
	//
	//		UINT8* pVertexDataBegin = nullptr;
	//		D3D12_RANGE stReadRange = { 0, 0 };
	//		ThrowIfFailed(m_vertexBuffer->Map(
	//			0
	//			, &stReadRange
	//			, reinterpret_cast<void**>(&pVertexDataBegin)));
	//
	//		memcpy(pVertexDataBegin
	//			, TriangleVertices
	//			, sizeof(TriangleVertices));
	//
	//		m_vertexBuffer->Unmap(0, nullptr);
	//
	//		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	//		m_vertexBufferView.StrideInBytes = sizeof(VERTEX);
	//		m_vertexBufferView.SizeInBytes = VertexBufferSize;
	//	}
	//	void RenderResourceManager::CreateFenceAndEvent()
	//	{
	//		ThrowIfFailed(m_device->CreateFence(m_fenceValues[m_frameIndex], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
	//		m_fenceValues[m_frameIndex]++;
	//
	//		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	//		if (m_fenceEvent == nullptr)
	//		{
	//			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	//		}
	//	}
	//	void RenderResourceManager::CreateBarrier()
	//	{
	//		m_beginResBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	//		m_beginResBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	//		m_beginResBarrier.Transition.pResource = m_renderTarget.Get();
	//		m_beginResBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	//		m_beginResBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	//		m_beginResBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	//
	//		
	//		m_endResBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	//		m_endResBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	//		m_endResBarrier.Transition.pResource = m_renderTarget.Get();
	//		m_endResBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	//		m_endResBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	//		m_endResBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	//	}
	//	void RenderResourceManager::run()
	//	{
	//		/*m_commandList->Close();*/
	//		////命令分配器先Reset一下
	//		ThrowIfFailed(m_commandAllocator->Reset());
	//		m_commandList->Close();
	//		//Reset命令列表，并重新指定命令分配器和PSO对象
	//		ThrowIfFailed(m_commandList->Reset(m_commandAllocator.Get(), NULL));
	//
	//		// Indicate a state transition on the resource usage.
	//		mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
	//			D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	//
	//		// Clear the back buffer and depth buffer.
	//		mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	//		mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
	//		////开始记录命令
	//		//m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());
	//		//m_commandList->SetPipelineState(m_pipelineState.Get());
	//		//m_commandList->RSSetViewports(1, &m_viewPort);
	//		//m_commandList->RSSetScissorRects(1, &m_scissorRect);
	//
	//		//// 通过资源屏障判定后缓冲已经切换完毕可以开始渲染了
	//		//m_beginResBarrier.Transition.pResource = m_renderTarget.Get();
	//		//m_commandList->ResourceBarrier(1, &m_beginResBarrier);
	//
	//		////设置渲染目标
	//		//D3D12_CPU_DESCRIPTOR_HANDLE rtvhandle= DW.GetRenderTargetView();
	//		//m_commandList->OMSetRenderTargets(1, &rtvhandle, FALSE, nullptr);
	//
	//		//// 继续记录命令，并真正开始新一帧的渲染
	//		//const float							faClearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	//		//m_commandList->ClearRenderTargetView(DW.GetRenderTargetView(), faClearColor, 0, nullptr);
	//		//m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//		//m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	//
	//		////Draw Call！！！
	//		//m_commandList->DrawInstanced(3, 1, 0, 0);
	//
	//		////又一个资源屏障，用于确定渲染已经结束可以提交画面去显示了
	//		//m_endResBarrier.Transition.pResource = m_renderTarget.Get();
	//		//m_commandList->ResourceBarrier(1, &m_endResBarrier);
	//		////关闭命令列表，可以去执行了
	//		//ThrowIfFailed(m_commandList->Close());
	//
	//		////执行命令列表
	//		//ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	//		//m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
	//
	//		////提交画面
	//		//ThrowIfFailed(DW.GetSwapChain()->Present(1, 0));
	//
	//		////开始同步GPU与CPU的执行，先记录围栏标记值
	//		//const UINT64 n64CurrentFenceValue = m_fenceValues[m_frameIndex];
	//		//ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), n64CurrentFenceValue));
	//		//m_fenceValues[m_frameIndex]++;
	//		//ThrowIfFailed(m_fence->SetEventOnCompletion(n64CurrentFenceValue, m_fenceEvent));
	//	}

	void RenderResourceManager::AddPass(renderpass::Pass_Mat_Info* PassInfo)
	{
		if(PassInfo->GetPassInfoType() == renderpass::PassInfoType::Depth)
		{
			AddDepthPass(dynamic_cast<renderpass::DepthPassInfo*>(PassInfo));
		}
		if (PassInfo->GetPassInfoType() == renderpass::PassInfoType::GBuffer)
		{
			AddGBufferPass(dynamic_cast<renderpass::GBufferPassInfo*>(PassInfo));
		}
	}

	void RenderResourceManager::AddDepthPass(renderpass::DepthPassInfo* PassInfo)
	{
		//  Resource & View
		/*auto* VP = &(PassInfo->Vertex_Attribute_Stream[ResourceUsage::VBV].VertexData);
		auto* IP = &(PassInfo->Index_Stream[ResourceUsage::IBV].VertexData);

		ComPtr<ID3D12Resource>	UploadBuffer1;
		ComPtr<ID3D12Resource>	UploadBuffer2;

		auto PassName = PassInfo->Getname();

		ResourceIDs.emplace(PassName+"VertexBuffer", FrameResourceId);
		API_Resources[FrameResourceId++]  = d3dUtil::CreateDefaultBuffer
		(m_device.Get(), m_commandList.Get(), VP->data(), VP->size() * 4, UploadBuffer1);

		ResourceIDs.emplace(PassName+"IndexBuffer", FrameResourceId);
		API_Resources[FrameResourceId++] = d3dUtil::CreateDefaultBuffer
		(m_device.Get(), m_commandList.Get(), IP->data(), IP->size() * 4, UploadBuffer2);*/

		//					特殊资源只提供一个名字就行 , 格式啥的交给Manager去匹配
		
		
		//	PSO
		auto RenderPSO = PassInfo->RenderPSO;

		D3D12_GRAPHICS_PIPELINE_STATE_DESC  PSO;
		ZeroMemory(&PSO, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		//			InputView
		auto InputViews = PassInfo->RenderPSO.InputViews;
		std::vector<D3D12_INPUT_ELEMENT_DESC> InputDESC;
		for (int i = 0; i <InputViews.size(); i++)
		{
			InputDESC.push_back(CreateInputDESC(InputViews[i]));
		}
		PSO.InputLayout = { InputDESC.data(),(uint32_t)InputDESC.size() };
		//			RootSignature
		PSO.pRootSignature = NULL;
		//			Raster;
		PSO.RasterizerState = CreateDefaultRasterDESC(PassInfo->RenderPSO.Rasterize);
		//			BlendState
		PSO.BlendState = CreateDefaultOpacityBlendState();
		//			DepthStencilState
		PSO.DepthStencilState = CreateDefaultD_S_State();
		//			SampleMask
		PSO.SampleMask = UINT_MAX;
		//			PrimitiveTopolopgType
		PSO.PrimitiveTopologyType = GetDX12Topology(RenderPSO.Topolopy);
		//			RenderTargets
		int i = 0;
		for (const auto& Res : PassInfo->ResourceInfos)
		{
			if (Res.first == ResourceUsage::RTV)
			{
				PSO.NumRenderTargets++;
				PSO.RTVFormats[i++] = Get_DXGI_Format(Res.second.Foramt);
			}
			if (Res.first == ResourceUsage::DSV)
			{
				PSO.DSVFormat = Get_DXGI_Format(Res.second.Foramt);
			}
		}
		//PSO.SampleDesc.Count = m4xMsaaState ? 4 : 1;
		//PSO.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
		//PSO.DSVFormat = Get_DXGI_Format(PassInfo->ResourceInfos[ResourceUsage::DSV].Foramt);
	
		//			Shader :  比较从前往后传的Shader参数 与 缓存Shader的参数.
		//			是重新编译		还是用缓存的
		// 
		//			还是从RenderPSO里吧Shader除掉吧 , 从前往后传vector不好整啊
		PSO.VS =
		{
			reinterpret_cast<BYTE*>(mShaders[RenderPSO.Shaders[0].ShaderName]->GetBufferPointer()),
			mShaders[RenderPSO.Shaders[0].ShaderName]->GetBufferSize()
		};
		PSO.PS =
		{
			reinterpret_cast<BYTE*>(mShaders[RenderPSO.Shaders[1].ShaderName]->GetBufferPointer()),
			mShaders[RenderPSO.Shaders[1].ShaderName]->GetBufferSize()
		};

		mPSOs.emplace("DepthPass",  new ComPtr<ID3D12PipelineState>);
		ThrowIfFailed(m_device->CreateGraphicsPipelineState(&PSO, IID_PPV_ARGS(&mPSOs["DepthPass"])));
		//
		// PSO for shadow map pass.
		//
		//D3D12_GRAPHICS_PIPELINE_STATE_DESC smapPsoDesc = PSO;
		//smapPsoDesc.RasterizerState.DepthBias = 100000;
		//smapPsoDesc.RasterizerState.DepthBiasClamp = 0.0f;
		//smapPsoDesc.RasterizerState.SlopeScaledDepthBias = 1.0f;
		//smapPsoDesc.pRootSignature = mRootSignature.Get();
		//smapPsoDesc.VS =
		//{
		//	reinterpret_cast<BYTE*>(mShaders["shadowVS"]->GetBufferPointer()),
		//	mShaders["shadowVS"]->GetBufferSize()
		//};
		//smapPsoDesc.PS =
		//{
		//	reinterpret_cast<BYTE*>(mShaders["shadowOpaquePS"]->GetBufferPointer()),
		//	mShaders["shadowOpaquePS"]->GetBufferSize()
		//};

		//// Shadow map pass does not have a render target.
		//smapPsoDesc.RTVFormats[0] = DXGI_FORMAT_UNKNOWN;
		//smapPsoDesc.NumRenderTargets = 0;
		//ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&smapPsoDesc, IID_PPV_ARGS(&mPSOs["shadow_opaque"])));

		////
		//// PSO for debug layer.
		////
		//D3D12_GRAPHICS_PIPELINE_STATE_DESC debugPsoDesc = PSO;
		//debugPsoDesc.pRootSignature = mRootSignature.Get();
		//debugPsoDesc.VS =
		//{
		//	reinterpret_cast<BYTE*>(mShaders["debugVS"]->GetBufferPointer()),
		//	mShaders["debugVS"]->GetBufferSize()
		//};
		//debugPsoDesc.PS =
		//{
		//	reinterpret_cast<BYTE*>(mShaders["debugPS"]->GetBufferPointer()),
		//	mShaders["debugPS"]->GetBufferSize()
		//};
		//ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&debugPsoDesc, IID_PPV_ARGS(&mPSOs["debug"])));

		////
		//// PSO for sky.
		////
		//D3D12_GRAPHICS_PIPELINE_STATE_DESC skyPsoDesc = PSO;

		//// The camera is inside the sky sphere, so just turn off culling.
		//skyPsoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

		//// Make sure the depth function is LESS_EQUAL and not just LESS.  
		//// Otherwise, the normalized depth values at z = 1 (NDC) will 
		//// fail the depth test if the depth buffer was cleared to 1.
		//skyPsoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		//skyPsoDesc.pRootSignature = mRootSignature.Get();
		//skyPsoDesc.VS =
		//{
		//	reinterpret_cast<BYTE*>(mShaders["skyVS"]->GetBufferPointer()),
		//	mShaders["skyVS"]->GetBufferSize()
		//};
		//skyPsoDesc.PS =
		//{
		//	reinterpret_cast<BYTE*>(mShaders["skyPS"]->GetBufferPointer()),
		//	mShaders["skyPS"]->GetBufferSize()
		//};
		//ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&skyPsoDesc, IID_PPV_ARGS(&mPSOs["sky"])));


		
		//FrameGraphicsPassResource Resource;
	}

	void RenderResourceManager::AddGBufferPass(renderpass::GBufferPassInfo* PassInfo)
	{
		auto RenderPSO = PassInfo->RenderPSO;



		D3D12_GRAPHICS_PIPELINE_STATE_DESC  PSO;
		ZeroMemory(&PSO, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		//			InputView
		auto InputViews = RenderPSO.InputViews;
		std::vector<D3D12_INPUT_ELEMENT_DESC> InputDESC;
		for (int i = 0; i < InputViews.size(); i++)
		{
			InputDESC.push_back(CreateInputDESC(InputViews[i]));
		}
		PSO.InputLayout = { InputDESC.data(),(uint32_t)InputDESC.size() };
		//			RootSignature
		PSO.pRootSignature = NULL;
		//			Raster;
		PSO.RasterizerState = CreateDefaultRasterDESC(RenderPSO.Rasterize);
		//			BlendState
		PSO.BlendState = CreateDefaultOpacityBlendState();
		//			DepthStencilState
		PSO.DepthStencilState = CreateDefaultD_S_State();
		//			SampleMask
		PSO.SampleMask = UINT_MAX;
		//			PrimitiveTopolopgType
		PSO.PrimitiveTopologyType = GetDX12Topology(RenderPSO.Topolopy);
		//			RenderTargets
		int i = 0;
		for (const auto &Res : PassInfo->Resources)
		{
			if (Res.first == ResourceUsage::RTV)
			{
				PSO.NumRenderTargets++;
				PSO.RTVFormats[i++] = Get_DXGI_Format(Res.second.Foramt);
			}
			if (Res.first == ResourceUsage::DSV)
			{
				PSO.DSVFormat = Get_DXGI_Format(Res.second.Foramt);
			}
		}
		//			RenderTarget Format
		//PSO.RTVFormats[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//PSO.RTVFormats[1] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//PSO.RTVFormats[2] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//PSO.RTVFormats[3] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//
		//PSO.SampleDesc.Count = m4xMsaaState ? 4 : 1;
		//PSO.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
		//PSO.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

		//			Shader :  比较从前往后传的Shader参数 与 缓存Shader的参数.
		//			是重新编译		还是用缓存的
		PSO.VS =
		{
			reinterpret_cast<BYTE*>(mShaders[RenderPSO.Shaders[0].ShaderName]->GetBufferPointer()),
			mShaders[RenderPSO.Shaders[0].ShaderName]->GetBufferSize()
		};
		PSO.PS =
		{
			reinterpret_cast<BYTE*>(mShaders[RenderPSO.Shaders[1].ShaderName]->GetBufferPointer()),
			mShaders[RenderPSO.Shaders[1].ShaderName]->GetBufferSize()
		};

		mPSOs.emplace("DepthPass", new ComPtr<ID3D12PipelineState>);
		ThrowIfFailed(m_device->CreateGraphicsPipelineState(&PSO, IID_PPV_ARGS(&mPSOs["DepthPass"])));

	}

	void RenderResourceManager::Run()
	{

		ThrowIfFailed(m_commandAllocator->Reset());

		(((HRESULT)(m_commandList.Get()->Reset(m_commandAllocator.Get(), 0))) < 0);

		for (auto PassInfo : PassInfos)
		{
			//PassInfo->ExcuteLamda(CmdList, FrameGraphicsPassResources[PassInfo->Getname()]);
			PassInfo->ExcuteLamda(m_commandList.Get(), GetFrameGraphicsResource(PassInfo->GetPassName()));
		}
	}
//	void RenderResourceManager::CreatePassResource(Engine::Render::renderpass::RenderPassInfo PPI)
//	{
//		CreatePSO();
//		CreateBuffer();
//		CreateViews();
//		
//	}
//
//	/// <summary>
//	/// ////////////////////////////////CreatePassResource//////////////////////////////////////////
//	/// </summary>
//	/// <param name="LPI"></param>
//	void RenderResourceManager::CreateLearnPassResource(Engine::Render::renderpass::LearnPassInfo LPI)
//	{
//		//
//		CreatePSO();
//		CreateVertexBuffer();
//		CreateIndexBuffer();
//	}
//}