#pragma once

#include "Device_Windows.h"
#include "Scene/Scene.hpp"
#include "d3dUtil.h"
#include "RenderPass.h"
#include "Buffer.h"

namespace Engine::Render::resource
{
	/// <summary>
	/// //////////////////////////////////////////	C O M	����ָ�� : ��������ͷŵ�����
	/// </summary>
	
	struct FrameGraphicsPassResource
	{
	public:
		//        �Ż���ֱ�Ӹ�handle?  ��RRM��ú���ֱ�Ӱ�handle����,Ȼ��Ԥ��һ��λ��,�Ȼ��չ������ƶ���ȥ.
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	RTV_Heap;
		//UINT64											RTV_StartIndex;
		//UINT64											RTV_DescriptorSize;

		Microsoft::WRL::ComPtr<ID3D12PipelineState>		PSO;
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	SRV_Heap;
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	CBV_Heap;
		std::array<ID3D12DescriptorHeap* const,2>		Heaps;
		std::vector<uint32_t>							Constants;
		//		Constants	�й���Heap���±�ļ��㷽ʽ :  (resource_handle - starthandle) / size;
		//		��Ҫ��ӳ�����ҵ����pass�����resource , Ȼ����ܼ���Index;
		//		PassInfo.Input_SRV_Resource.names;	PassInfo.Input_CBV_Resource.names;
		//		handle / pointer	 RRM::GetXXX(Rname)  { return un_map[name].handle; }		ֱ�Ӹ�handle��������Դָ���ٻ�ȡhandle?
		//uint32_t Descriptor::GetDescriptorIndex(const DescriptorHandle& descriptorHandle) const
	/*	{
			return static_cast<uint32_t>
			(descriptorHandle.gpuDescriptorHandle.ptr -mDescriptorHandleFromStart.gpuDescriptorHandle.ptr) /mDescriptorSize);
		}*/

		//std::unordered_map<std::string, D3D12_CPU_DESCRIPTOR_HANDLE*>				RenderTargets;
		std::vector<D3D12_VERTEX_BUFFER_VIEW>			VBV;
		D3D12_INDEX_BUFFER_VIEW*						IBV;
		//		���Ʋ�������,Ҫ��ȥ��װһ , ������?
		//		�� lamda ��ָ��Ҫ�õ���Դ
		//		Ȼ������һ��ȥ ��ָ����Դ�� API���ݷŵ�API_cmdlist��ȥ..

		D3D12_CPU_DESCRIPTOR_HANDLE*					DSV;
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>		RTVs;

		//	ViewPorts
		//	Scissors;

		//	  ����Ż���ָ��  ʹ��ʱ�ǵ���	Dynamic_cast	ת��һ��
	};
	struct FrameComputePassResource
	{
		
	};

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
		void CreatePassResource(Engine::Render::renderpass::Pass_Mat_Info PMI);
		//void CreateLearnPassResource(Engine::Render::renderpass::LearnPassInfo LPI);

		FrameGraphicsPassResource* GetFrameGraphicsResource(std::string name) {
			return &FrameGraphicsPassResources[name];
		};

		FrameComputePassResource* GetFrameComputeResource(std::string name)
		{
			return &FrameComputePassResources[name];
		}

	private:

		//ͬ����Դ
		void CreateFenceAndEvent();
		void CreateBarrier();

		//V,I,C,Instance,T,U
		//��ͳһ��װ��Buffer������, ����д��֧���Ǹ���һ������?
		void CreateBuffer();
		void CreateVertexBuffer();

		void Create_API_VI_Buffer();

		

		
		void CreateRootSignature();


	private:
		//Device
		Device_Windows::DeviceWindows						DW;
		Microsoft::WRL::ComPtr<ID3D12Device>				m_device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>			m_commandQueue;
		//Device Update
		uint32_t											m_frameIndex;
		Microsoft::WRL::ComPtr<ID3D12Resource>				m_renderTarget;
		Microsoft::WRL::ComPtr<ID3D12Fence>					m_fence;
		UINT64												m_fenceValues[2];
		HANDLE												m_fenceEvent;
		//		һ��֡һ��Command Queue
		//		һ���߳�һ��Allocator
		//		һ��cmdlist�Ϳ���ͨ����ͬ�ӿڵ��� , Ȼ�����з��͸���Ӧ��Graphic,Compute,Copy����
		//		ͬ��:	֡	��Pass	СPass	�������(��������֮��)
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>		m_commandAllocator;
		D3D12_RESOURCE_BARRIER								m_beginResBarrier;
		D3D12_RESOURCE_BARRIER								m_endResBarrier;


	private:

		uint32_t	SRV_CBV_UAV_Descriptor_size	;
		uint32_t	Sampler_Descriptor_size;
		uint32_t GetDescriptorIndex(std::string name , Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	Heap)
		{	
			return static_cast<uint32_t>
			((API_GPU_handles[name].Get()->ptr - Heap.Get()->GetGPUDescriptorHandleForHeapStart().ptr) / SRV_CBV_UAV_Descriptor_size);
		}
		uint32_t GetSamplerIndex(std::string name, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	Heap)
		{
			return static_cast<uint32_t>
				((API_GPU_handles[name].Get()->ptr - Heap.Get()->GetGPUDescriptorHandleForHeapStart().ptr) / Sampler_Descriptor_size);
		}
		 //							Frame	Graphics  Runtime
//		struct FrameGraphicsPassResource
//		{
//			public:
//				//        �Ż���ֱ�Ӹ�handle?  ��RRM��ú���ֱ�Ӱ�handle����,Ȼ��Ԥ��һ��λ��,�Ȼ��չ������ƶ���ȥ.
//				//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	RTV_Heap;
//				//UINT64											RTV_StartIndex;
//				//UINT64											RTV_DescriptorSize;
//
//				Microsoft::WRL::ComPtr<ID3D12PipelineState>		PSO;
//				Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	SRV_Heap;
//				Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	CBV_Heap;
//				std::vector<uint32_t>							Constants;
//				//		Constants	�й���Heap���±�ļ��㷽ʽ :  (resource_handle - starthandle) / size;
//				//		��Ҫ��ӳ�����ҵ����pass�����resource , Ȼ����ܼ���Index;
//				//		PassInfo.Input_SRV_Resource.names;	PassInfo.Input_CBV_Resource.names;
//				//		handle / pointer	 RRM::GetXXX(Rname)  { return un_map[name].handle; }		ֱ�Ӹ�handle��������Դָ���ٻ�ȡhandle?
//				//uint32_t Descriptor::GetDescriptorIndex(const DescriptorHandle& descriptorHandle) const
//			/*	{
//					return static_cast<uint32_t>   
//					(descriptorHandle.gpuDescriptorHandle.ptr -mDescriptorHandleFromStart.gpuDescriptorHandle.ptr) /mDescriptorSize);
//				}*/
//
//				std::unordered_map<std::string, Buffer::RenderTargetBuffer*>				RenderTargets;
//				D3D12_VERTEX_BUFFER_VIEW*						VBV;
//				D3D12_VERTEX_BUFFER_VIEW*						IBV;
//				D3D12_CPU_DESCRIPTOR_HANDLE*					DSV;
//
//
//				//	  ����Ż���ָ��  ʹ��ʱ�ǵ���	Dynamic_cast	ת��һ��
//		};
//
//		//						<P_Mat_name , GR>
		std::unordered_map<std::string, FrameGraphicsPassResource>								FrameGraphicsPassResources;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		
//		//					Frame	 Compute	Runtime
//		struct FrameComputePassResource
//		{
//
//		};
		//						<P_Ferture_name , CR>
		std::unordered_map<std::string, FrameComputePassResource>								FrameComputePassResources;




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//								Frames  Resource
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//									Cache	&	Debug
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>>										Shaders;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_GRAPHICS_PIPELINE_STATE_DESC>>				PSO_DESCs;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>	>							PSO_States;
			
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//									ALL_API_Resource								
		std::unordered_map<std::string, Microsoft::WRL::ComPtr< ID3D12Resource>	>								API_Resources;
		std::unordered_map<std::string, Microsoft::WRL::ComPtr< CD3DX12_GPU_DESCRIPTOR_HANDLE>	>				API_GPU_handles;





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