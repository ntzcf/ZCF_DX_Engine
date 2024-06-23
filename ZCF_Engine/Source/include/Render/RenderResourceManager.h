#pragma once

#include "Device_Windows.h"
#include "Scene/Scene.hpp"
#include "Helper.h"
#include "RenderPass.h"

namespace Engine::Render::resource
{
	class RenderResourceManager
	{

	public:
		RenderResourceManager() {};
		void Init(HWND window, int width, int height);
		void CreateCmdList();
		void CreateRootSignature();
		void CreatePSO();
		void CreateVertexBuffer();
		void CreateFenceAndEvent();
		void CreateBarrier();

		void Update();
		void run();
		~RenderResourceManager() {};

		//void CreatePassResource(Engine::Render::renderpass::RenderPassInfo);
		void CreateLearnPassResource(Engine::Render::renderpass::LearnPassInfo LPI);



	private:
		//Device
		Device_Windows::DeviceWindows						DW;
		Microsoft::WRL::ComPtr<ID3D12Device>				m_device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>			m_commandQueue;
		//Device Update
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>		m_commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_renderTarget;
		uint32_t											m_frameIndex;
		
		//Shader
		//PSO
		//Buffer
		
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
		Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		m_cbvHeap;
		UINT												m_cbvDescriptorSize;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;
		//ModelViewProjectionConstantBuffer					m_constantBufferData;
		UINT8* m_mappedConstantBuffer;
		D3D12_VIEWPORT										m_viewPort;
		D3D12_RECT											m_scissorRect;

		Microsoft::WRL::ComPtr<ID3D12Fence>					m_fence;
		UINT64												m_fenceValues[2];
		HANDLE												m_fenceEvent;
		D3D12_RESOURCE_BARRIER								m_beginResBarrier;
		D3D12_RESOURCE_BARRIER								m_endResBarrier;

		TCHAR												ShaderPath[MAX_PATH] = {};
		Microsoft::WRL::ComPtr<ID3DBlob>					m_vertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob>					m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;



		//API_Resource_Manager
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12RootSignature>	>			RootSignatures;

	};
}