#pragma once

#include "Device_Windows.h"
#include "Scene/Scene.hpp"
#include "Helper.h"
#include "RenderPass.h"
#include "Buffer.h"

namespace Engine::Render::resource
{
	class RenderResourceManager
	{
		struct FrameGraphicsResource;
		struct FrameComputeResource;


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

		FrameGraphicsResource* GetFrameGraphicsResource(std::string name) {
			return &FrameGraphicsPassResources[name];
		};

		FrameComputeResource GetFrameComputeResource(std::string name)
		{
			return FrameComputePassResources[name];
		}

	private:

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
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_renderTarget;

		Microsoft::WRL::ComPtr<ID3D12Fence>					m_fence;
		UINT64												m_fenceValues[2];
		HANDLE												m_fenceEvent;
		D3D12_RESOURCE_BARRIER								m_beginResBarrier;
		D3D12_RESOURCE_BARRIER								m_endResBarrier;





		struct FrameGraphicsResource
		{
		public:
			
			Microsoft::WRL::ComPtr<ID3D12PipelineState>		PSO;
			//        �Ż���ֱ�Ӹ�handle?  ��RRM��ú���ֱ�Ӱ�handle����,Ȼ��Ԥ��һ��λ��,�Ȼ��չ������ƶ���ȥ.
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	RTV_Heap;
			UINT64											RTV_StartIndex;
			UINT64											RTV_DescriptorSize;
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	SRV_Heap;
			Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	CBV_Heap;
			D3D12_VERTEX_BUFFER_VIEW*						VBV;
			D3D12_VERTEX_BUFFER_VIEW*						IBV;
			CD3DX12_CPU_DESCRIPTOR_HANDLE*					DSV;


			//	  ����Ż���ָ��  ʹ��ʱ�ǵ���	Dynamic_cast	ת��һ��
			std::vector<Buffer::V_I_Buffer*>											V_I_Buffers;
			//RTV
			std::unordered_map<std::string, Buffer::RenderTargetBuffer*>				RenderTargets;
			//SRV
			
			//CBV

		};

		std::unordered_map<std::string, FrameGraphicsResource>								FrameGraphicsPassResources;
		
		struct FrameComputeResource
		{

		};

		std::unordered_map<std::string, FrameComputeResource>								FrameComputePassResources;
		
		//
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>>										Shaders;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_GRAPHICS_PIPELINE_STATE_DESC>>				PSO_DESCs;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>			>					PSO_States;
			
		//																	
		std::unordered_map<std::string, Microsoft::WRL::ComPtr< ID3D12Resource>	>								API_Resources;


		//
		std::vector<Buffer::V_I_Buffer>					V_I_Buffers;
		std::vector<Buffer::ConstantBuffer>				ConstantBuffers;
		//Constant  ------- Bindless
		std::vector<Buffer::InstanceBuffer>				InstanceBuffers;






		//ID3D12PipelineState*				GetPSO(std::string Pname);
		//ID3D12Resource*						GetResource(std::string Rname);
		//ID3D12Resource*						GetRenderTargets(std::string Pname);
		//CD3DX12_CPU_DESCRIPTOR_HANDLE*		GetRTVs(std::string Pname);//RTV Heap �� ��ӦResource �� Handle
		//D3D12_VERTEX_BUFFER_VIEW*			GetVBV(std::string Pname);
		//D3D12_VERTEX_BUFFER_VIEW*			GetIBV(std::string Pname);
		//void 								GetCBV(std::string Pname);



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