#pragma once
#include "Helper.h"


namespace Engine::Render::resource::Device_Windows
{

	class DeviceWindows
	{
	public:
		DeviceWindows();
		~DeviceWindows() {};





	public:
		void Init(HWND window, int width, int height);
		void Update();

		CD3DX12_CPU_DESCRIPTOR_HANDLE GetRenderTargetView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_currentFrame, m_rtvDescriptorSize);
		}
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const
		{
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_dsvHeap->GetCPUDescriptorHandleForHeapStart());
		}
		//UpdateRenderTargetSize();
		// 
		// 
		// 
		//������
		ID3D12Device*				GetD3DDevice()					const {	return m_d3dDevice.Get();							}
		IDXGISwapChain1*			GetSwapChain()					const {	return m_swapChain.Get();							}
		ID3D12Resource*				GetRenderTarget()				const {	return m_renderTargets[m_currentFrame].Get();		}
		ID3D12Resource*				GetDepthStencil()				const {	return m_depthStencil.Get();						}		
		ID3D12CommandQueue*			GetCommandQueue()				const {	return m_commandQueue.Get();						}
		ID3D12CommandAllocator*		GetCommandAllocator()			const {	return m_commandAllocators[m_currentFrame].Get();	}
		DXGI_FORMAT					GetBackBufferFormat()			const {	return m_backBufferFormat;							}
		DXGI_FORMAT					GetDepthBufferFormat()			const {	return m_depthBufferFormat;							}
		D3D12_VIEWPORT				GetScreenViewport()				const {	return m_screenViewport;							}
		DirectX::XMFLOAT4X4			GetOrientationTransform3D()		const {	return m_orientationTransform3D;					}
		UINT						GetCurrentFrameIndex()			const {	return m_currentFrame;								}

	private:
		//��Դ:�豸,����,�豸���,�������,�ۺ����
		//�ӿ�:�����豸,������Դ,������Դ��
		//�豸���
		void CreateDeviceDependentResources();
		void CreateDevice();
		void CreateCommandQueue();// and Allocator
		void Create_rtv_dsv_heaps();
		void CreatesRTVs();
		void CreatesDSVs();
		void CreateFence();
		void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);


		//windows���:RT SwapChain �Լ���ز���
		//void CreateWindows();
		void CreateWindowSizeDependentResources();
		void CreateSwapChain();




		HWND											window = NULL;
		uint32_t										m_windowWidth;
		uint32_t										m_windowHeight;
		uint32_t										m_frameCount = 2;
		uint32_t										m_currentFrame = 0;
		Microsoft::WRL::ComPtr<ID3D12Device>			m_d3dDevice;
		Microsoft::WRL::ComPtr<IDXGIFactory7>			m_dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGISwapChain3>			m_swapChain;
		Microsoft::WRL::ComPtr<ID3D12Resource>			m_renderTargets[2];
		Microsoft::WRL::ComPtr<ID3D12Resource>			m_depthStencil;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_rtvHeap;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_dsvHeap;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>		m_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>	m_commandAllocators[2];
		DXGI_FORMAT										m_backBufferFormat= DXGI_FORMAT_R8G8B8A8_UNORM;
		DXGI_FORMAT										m_depthBufferFormat= DXGI_FORMAT_D32_FLOAT;
		D3D12_VIEWPORT									m_screenViewport;
		UINT											m_rtvDescriptorSize;
		bool											m_deviceRemoved;

		// CPU/GPU ͬ����
		Microsoft::WRL::ComPtr<ID3D12Fence>				m_fence;
		UINT64											m_fenceValues[2];
		HANDLE											m_fenceEvent;

		// ������豸���ԡ�
		float											m_dpi;

		// ���ǽ���Ӧ�ô��ص� DPI����������Ӧ���Ƿ�֧�ָ߷ֱ�����Ļ��
		float											m_effectiveDpi;

		// ������ʾ�����ת����
		DirectX::XMFLOAT4X4								m_orientationTransform3D;


	};
}





















