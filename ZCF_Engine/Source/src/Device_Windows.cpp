#include "Render/Device_Windows.h"
#include "Render/SrcRenderHelper.h"

//using namespace Microsoft::WRL;
//using namespace DirectX;
//using namespace Engine::Render;

namespace Engine::Render::resource::Device_Windows
{
	DeviceWindows::DeviceWindows() :
		m_screenViewport(),
		m_rtvDescriptorSize(0),
		m_fenceEvent(0),
		m_fenceValues{},
		m_dpi(-1.0f),
		m_effectiveDpi(-1.0f),
		m_deviceRemoved(false),
		m_windowHeight(0),
		m_windowWidth(0)
	{
		CreateDeviceDependentResources();
	}


	void DeviceWindows::Init(HWND window,int weight,int height)
	{
		m_windowWidth = weight;
		m_windowHeight = height;
		this->window = window;
		CreateWindowSizeDependentResources();

	}

	void DeviceWindows::CreateDeviceDependentResources()
	{
		CreateDevice();
		CreateCommandQueue();
		Create_rtv_dsv_heaps();
	}
	void resource::Device_Windows::DeviceWindows::Update()
	{ 
		m_currentFrame = m_swapChain->GetCurrentBackBufferIndex();
	}

	void DeviceWindows::CreateWindowSizeDependentResources()
	{
		//先来个围栏,确保是可以重建的时候
		CreateSwapChain();
		CreatesRTVs();
		CreatesDSVs();
	}

	void DeviceWindows::CreateSwapChain()
	{
		if (m_swapChain != nullptr)
		{
			// 如果交换链已存在，请调整其大小。
			HRESULT hr = m_swapChain->ResizeBuffers(m_frameCount, m_windowWidth, m_windowHeight, m_backBufferFormat, 0);

			if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
			{
				// 如果出于任何原因移除了设备，将需要创建一个新的设备和交换链。
				m_deviceRemoved = true;

				// 请勿继续执行此方法。会销毁并重新创建 DeviceResources。
				return;
			}
			else
			{
				ThrowIfFailed(hr);
			}
		}
		else
		{
			// 否则，使用与现有 Direct3D 设备相同的适配器新建一个。
			//DXGI_SCALING scaling = DisplayMetrics::SupportHighResolutions ? DXGI_SCALING_NONE : DXGI_SCALING_STRETCH;
			DXGI_SWAP_CHAIN_DESC1 stSwapChainDesc = {};
			stSwapChainDesc.BufferCount = m_frameCount;
			stSwapChainDesc.Width = m_windowWidth;
			stSwapChainDesc.Height = m_windowHeight;
			stSwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			stSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			stSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			stSwapChainDesc.SampleDesc.Count = 1;

			ComPtr<IDXGISwapChain1> swapChain;
			ThrowIfFailed(m_dxgiFactory->CreateSwapChainForHwnd(
				m_commandQueue.Get(),		// 交换链需要命令队列，Present命令要执行
				window,
				&stSwapChainDesc,
				nullptr,
				nullptr,
				&swapChain)
			);
			ThrowIfFailed(swapChain.As(&m_swapChain));
		}
	}

	void DeviceWindows::CreatesRTVs()
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvDescriptor(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
		for (UINT n = 0; n < m_frameCount; n++)
		{	
			
			ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n])));
			m_d3dDevice->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvDescriptor);
			rtvDescriptor.Offset(m_rtvDescriptorSize);

			WCHAR name[25];
			if (swprintf_s(name, L"m_renderTargets[%u]", n) > 0)
			{
				SetName(m_renderTargets[n].Get(), name);
			}
		}
	}

	void DeviceWindows::CreatesDSVs()
	{
		D3D12_HEAP_PROPERTIES depthHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

		D3D12_RESOURCE_DESC depthResourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(m_depthBufferFormat, 
			m_windowWidth, m_windowHeight, 1, 1);
		depthResourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		CD3DX12_CLEAR_VALUE depthOptimizedClearValue(m_depthBufferFormat, 1.0f, 0);

		ThrowIfFailed(m_d3dDevice->CreateCommittedResource(
			&depthHeapProperties,
			D3D12_HEAP_FLAG_NONE,
			&depthResourceDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&depthOptimizedClearValue,
			IID_PPV_ARGS(&m_depthStencil)
		));

		NAME_D3D12_OBJECT(m_depthStencil);

		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = m_depthBufferFormat;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

		m_d3dDevice->CreateDepthStencilView(m_depthStencil.Get(), &dsvDesc, m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
	}

	void DeviceWindows::CreateDevice()
	{
		#if defined(_DEBUG)
		// 如果项目处于调试生成阶段，请通过 SDK 层启用调试。
		{
			Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
			{
				debugController->EnableDebugLayer();
			}
		}
		#endif

		ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&m_dxgiFactory)));

		Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
		GetHardwareAdapter(&adapter);

		// 创建 Direct3D 12 API 设备对象
		HRESULT hr = D3D12CreateDevice
		(
			adapter.Get(),					// 硬件适配器。
			D3D_FEATURE_LEVEL_12_1,			// 此应用可以支持的最低功能级别。
			IID_PPV_ARGS(&m_d3dDevice)		// 返回创建的 Direct3D 设备。
		);

		#if defined(_DEBUG)
		if (FAILED(hr))
		{
			// 如果初始化失败，则回退到 WARP 设备。
			// 有关 WARP 的详细信息，请参阅: 
			// https://go.microsoft.com/fwlink/?LinkId=286690

			Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
			ThrowIfFailed(m_dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

			hr = D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3dDevice));
		}
		#endif

		ThrowIfFailed(hr);

	}

	void DeviceWindows::CreateCommandQueue()
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		ThrowIfFailed(m_d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));
		NAME_D3D12_OBJECT(m_commandQueue);
		
		//Allocators
		for (UINT n = 0; n < m_frameCount; n++)
		{
			ThrowIfFailed(
				m_d3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocators[n]))
			);
		}

	}

	void DeviceWindows::Create_rtv_dsv_heaps()
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = m_frameCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));
		NAME_D3D12_OBJECT(m_rtvHeap);

		m_rtvDescriptorSize = m_d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
		dsvHeapDesc.NumDescriptors = 1;
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(m_d3dDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_dsvHeap)));
		NAME_D3D12_OBJECT(m_dsvHeap);

	}

	void DeviceWindows::CreateFence()
	{
		ThrowIfFailed(m_d3dDevice->CreateFence(m_fenceValues[m_currentFrame], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		m_fenceValues[m_currentFrame]++;

		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (m_fenceEvent == nullptr)
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}

	}
	
	void DeviceWindows::GetHardwareAdapter(IDXGIAdapter1** ppAdapter)
	{
		ComPtr<IDXGIAdapter1> adapter;
		*ppAdapter = nullptr;

		for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != m_dxgiFactory->EnumAdapters1(adapterIndex, &adapter); adapterIndex++)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);
			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// 不要选择基本呈现驱动程序适配器。
				continue;
			}

			// 检查适配器是否支持 Direct3D 12，但不要创建
			// 仍为实际设备。
			if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
			{
				break;
			}
		}

		*ppAdapter = adapter.Detach();
	}
}