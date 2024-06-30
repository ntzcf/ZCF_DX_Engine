#pragma once

#include "Device_Windows.h"
#include "Scene/Scene.hpp"
#include "d3dUtil.h"
#include "RenderPass.h"
#include "Buffer.h"

namespace Engine::Render::resource
{
	/// <summary>
	/// //////////////////////////////////////////	C O M	智能指针 : 无需管理释放等问题
	/// </summary>
	
	struct FrameGraphicsPassResource
	{
	public:
		//        优化成直接给handle?  由RRM算好后再直接把handle给出,然后预留一段位置,等回收过后再移动回去.
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	RTV_Heap;
		//UINT64											RTV_StartIndex;
		//UINT64											RTV_DescriptorSize;

		Microsoft::WRL::ComPtr<ID3D12PipelineState>		PSO;
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	SRV_Heap;
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	CBV_Heap;
		std::array<ID3D12DescriptorHeap* const,2>		Heaps;
		std::vector<uint32_t>							Constants;
		//		Constants	中关于Heap中下标的计算方式 :  (resource_handle - starthandle) / size;
		//		需要个映射来找到这个pass所需的resource , 然后才能计算Index;
		//		PassInfo.Input_SRV_Resource.names;	PassInfo.Input_CBV_Resource.names;
		//		handle / pointer	 RRM::GetXXX(Rname)  { return un_map[name].handle; }		直接给handle还是先资源指针再获取handle?
		//uint32_t Descriptor::GetDescriptorIndex(const DescriptorHandle& descriptorHandle) const
	/*	{
			return static_cast<uint32_t>
			(descriptorHandle.gpuDescriptorHandle.ptr -mDescriptorHandleFromStart.gpuDescriptorHandle.ptr) /mDescriptorSize);
		}*/

		//std::unordered_map<std::string, D3D12_CPU_DESCRIPTOR_HANDLE*>				RenderTargets;
		std::vector<D3D12_VERTEX_BUFFER_VIEW>			VBV;
		D3D12_INDEX_BUFFER_VIEW*						IBV;
		//		绘制参数不够,要再去封装一 , 两层吗?
		//		在 lamda 里指定要用的资源
		//		然后由下一层去 把指定资源的 API数据放到API_cmdlist上去..

		D3D12_CPU_DESCRIPTOR_HANDLE*					DSV;
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>		RTVs;

		//	ViewPorts
		//	Scissors;

		//	  如果放基类指针  使用时记得用	Dynamic_cast	转换一下
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

		//	注册<name , Resource> <pass , Descriptors > 
		//	再由lamda回调 : View.GPU_Address = Resource.GPU_Address 
		//	再由封装后的CmdList来负责 : 具体的API_CmdList 与 API_Resource绑定
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

		//同步资源
		void CreateFenceAndEvent();
		void CreateBarrier();

		//V,I,C,Instance,T,U
		//是统一封装成Buffer函数组, 还是写分支但是复用一个函数?
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
		//		一个帧一个Command Queue
		//		一个线程一个Allocator
		//		一个cmdlist就可以通过不同接口调用 , 然后自行发送给对应的Graphic,Compute,Copy引擎
		//		同步:	帧	大Pass	小Pass	命令队列(三种引擎之间)
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
//				//        优化成直接给handle?  由RRM算好后再直接把handle给出,然后预留一段位置,等回收过后再移动回去.
//				//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	RTV_Heap;
//				//UINT64											RTV_StartIndex;
//				//UINT64											RTV_DescriptorSize;
//
//				Microsoft::WRL::ComPtr<ID3D12PipelineState>		PSO;
//				Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	SRV_Heap;
//				Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	CBV_Heap;
//				std::vector<uint32_t>							Constants;
//				//		Constants	中关于Heap中下标的计算方式 :  (resource_handle - starthandle) / size;
//				//		需要个映射来找到这个pass所需的resource , 然后才能计算Index;
//				//		PassInfo.Input_SRV_Resource.names;	PassInfo.Input_CBV_Resource.names;
//				//		handle / pointer	 RRM::GetXXX(Rname)  { return un_map[name].handle; }		直接给handle还是先资源指针再获取handle?
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
//				//	  如果放基类指针  使用时记得用	Dynamic_cast	转换一下
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
		//CD3DX12_CPU_DESCRIPTOR_HANDLE*		GetRTVs(std::string Pname);//RTV Heap 中 对应Resource 的 Handle
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