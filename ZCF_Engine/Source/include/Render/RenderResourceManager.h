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
		void Update();
		void run();
		~RenderResourceManager() {};

		//	ע��<name , Resource> <pass , Descriptors > 
		//	����lamda�ص� : View.GPU_Address = Resource.GPU_Address 
		//	���ɷ�װ���CmdList������ : �����API_CmdList �� API_Resource��
		void CreatePassResource(Engine::Render::renderpass::RenderPassInfo PPI);
		void CreateLearnPassResource(Engine::Render::renderpass::LearnPassInfo LPI);

		ID3D12PipelineState*				GetPSO(std::string Pname);
		ID3D12Resource*						GetResource(std::string Rname);
		ID3D12Resource*						GetRenderTargets(std::string Pname);
		CD3DX12_CPU_DESCRIPTOR_HANDLE*		GetRTVs(std::string Pname);//RTV Heap �� ��ӦResource �� Handle
		D3D12_VERTEX_BUFFER_VIEW*			GetVBV(std::string Pname);
		D3D12_VERTEX_BUFFER_VIEW*			GetIBV(std::string Pname);
		void 								GetCBV(std::string Pname);
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_renderTarget;

	private:
		void CreateCmdList();
		//Root , Shader , Raster , InputView , RTVs&Format,DSV&Format , BlendState , SampleDesc


		//SRV CBV UAV DSV SOV RTV Sampler      VBV IBV   
		void CreateViews();

		//ͬ����Դ
		void CreateFenceAndEvent();
		void CreateBarrier();

		//V,I,C,Instance,T,U
		//��ͳһ��װ��Buffer������, ����д��֧���Ǹ���һ������?
		void CreateBuffer();
		void CreateVertexBuffer();

		void CreatePSO(renderpass::RenderPassInfo);
		void CreateRootSignature();


	private:
		//Device
		Device_Windows::DeviceWindows						DW;
		Microsoft::WRL::ComPtr<ID3D12Device>				m_device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>			m_commandQueue;
		//Device Update
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>		m_commandAllocator;
		uint32_t											m_frameIndex;
		
		
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>	m_commandList;
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
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		D3D12_VERTEX_BUFFER_VIEW							m_vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;



		struct FrameResource
		{

		};
		//				Pass
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12RootSignature>	>							RootSignatures;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>>										Shaders;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_GRAPHICS_PIPELINE_STATE_DESC>>				PSO_DESCs;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>			>					PSO_States;

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>															RTV_Heap;
		struct Handle_Array
		{
			CD3DX12_CPU_DESCRIPTOR_HANDLE  handles[8];
		};


		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>			>					PSO_States;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>			>					PSO_States;
		//std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12Resource>			>						RenderTargets;
		/*std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_GRAPHICS_PIPELINE_STATE_DESC>>			InputLayouts;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_RASTERIZER_DESC>	>						Rasterizers;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_BLEND_DESC>	>							BlendStates;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_DEPTH_STENCIL_DESC>	>					Depth_Stencils;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_PRIMITIVE_TOPOLOGY>	>					TopoLogys;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_SAMPLER_DESC>	>							Samplers;*/
		//PSO
		//
		// 
		//
		//std::unordered_map<std::string , Comptr<MyResource>>		MyResources
		//															DescriptorManager
		//															UploadBuffers
		//															Queues:G,C,Copy
		//																

	};
}