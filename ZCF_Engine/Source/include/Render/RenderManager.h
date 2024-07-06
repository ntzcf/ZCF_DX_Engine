#pragma once

#include "Device_Windows.h"
#include "d3dUtil.h"
#include "Scene/Scene.hpp"
#include "Materials.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "RenderPassInfo.h"

using namespace  Microsoft::WRL;

namespace Engine::Render
{
	/// <summary>
	/// //////////////////////////////////////////	C O M	智能指针 : 无需管理释放等问题
	/// </summary>
	
	struct FrameGraphicsPassResource
	{
		//        优化成直接给handle?  由RRM算好后再直接把handle给出,然后预留一段位置,等回收过后再移动回去.
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		RTV_Heap;
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
		//		handle / pointer	 RRM::GetXXX(Rname)  { return un_map[name].handle; }

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


		//FrameComputePassResource* GetFrameComputeResource(std::string name)
		//{
		//	return &FrameComputePassResources[name];
		//}

		void AddPass(renderpass::Pass_Mat_Info* PassInfo);
		void AddDepthPass(renderpass::DepthPassInfo* PassInfo);
		void AddGBufferPass(renderpass::GBufferPassInfo* PassInfo);
		void Run();

	private:

		void UploadData();
		void UploadBuffers();
		void UploadTextures();



		void CreateRootSignature();
		void CreateGraphicsPipeline();

		//同步资源
		//void CreateFenceAndEvent();
		//void CreateBarrier();		


	private:
		//Device
		resource::DeviceWindows						DW;
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
		//		一个cmdlist就可以通过不同接口调用 , 提交给Queue , 然后自行发送给对应的Graphic,Compute,Copy引擎
		//		同步:	帧	大Pass	小Pass	命令队列(三种引擎之间)
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>				m_commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>			m_commandList;
		//ID3D12GraphicsCommandList* CmdList;
		//D3D12_RESOURCE_BARRIER								m_beginResBarrier;
		//D3D12_RESOURCE_BARRIER								m_endResBarrier;


	private:

		uint32_t	FrameResourceId;

		uint32_t	SRV_CBV_UAV_Descriptor_size;
		uint32_t	Sampler_Descriptor_size;
		//				
		uint32_t GetDescriptorIndex(std::string name, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	Heap)
		{
			uint32_t ID = ResourceIDs[name];
			return static_cast<uint32_t>
				((API_GPU_handles[ID].Get()->ptr - Heap.Get()->GetGPUDescriptorHandleForHeapStart().ptr) / SRV_CBV_UAV_Descriptor_size);
		}
		uint32_t GetSamplerIndex(std::string name, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	Heap)
		{
			uint32_t ID = ResourceIDs[name];
			return static_cast<uint32_t>
				((API_GPU_handles[ID].Get()->ptr - Heap.Get()->GetGPUDescriptorHandleForHeapStart().ptr) / Sampler_Descriptor_size);
		}
		//							Frame	Graphics  Runtime
		FrameGraphicsPassResource& GetFrameGraphicsResource(std::string name)
		{
			return FrameGraphicsPassResources[name];
		};
		std::unordered_map<std::string, FrameGraphicsPassResource>				FrameGraphicsPassResources;
		//std::unordered_map<std::string, FrameComputePassResource>				FrameComputePassResources;
		//						<P_Ferture_name , CR>



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								Frames  Resource
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//									Cache	&	Debug
	//std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>>									Shaders;
	//std::unordered_map<std::string, Microsoft::WRL::ComPtr<D3D12_GRAPHICS_PIPELINE_STATE_DESC>>			PSO_DESCs;
		std::unordered_map<std::string, ComPtr<ID3D12PipelineState>>		mPSOs;
		std::unordered_map<std::string, ComPtr<ID3DBlob>>					mShaders;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//									ALL_Resource
		std::vector<renderpass::Pass_Mat_Info*>									PassInfos;
	//																
		std::string							ResourceFileDir = "E:/My projects/DX12_Engine/ZCF_Engine/Resources/";

		std::set<resource::CommonMaterial>										Materials;
		std::set<std::string>													TextureNames;

		STB_Texture_loader														TexLoader;
		std::unordered_map<std::string, resource::STB_Texture>					Textures;

	//	
		std::vector<ID3D12DescriptorHeap>										CPU_DescriptorHeaps;
		std::vector<ID3D12DescriptorHeap>										GPU_DescriptorHeaps;
		
		std::unordered_map<uint32_t , ComPtr< ID3D12Resource>>					API_Resources;
		
		std::unordered_map<std::string, uint32_t>								ResourceIDs;
		uint32_t	GetResourceId(std::string name) { return ResourceIDs[name]; }
	//			资源名 --------- Descriptor View ID : 可复用
	//		CPU端可以提前创好 , 用时复制
		std::unordered_map<uint32_t, ComPtr< D3D12_CPU_DESCRIPTOR_HANDLE>>		API_CPU_handles;
	//		GPU端的话 , 要根据Pass的设置来灵活调整 , 需要另外的管理方案
		//			待构思
		std::vector<ComPtr< D3D12_GPU_DESCRIPTOR_HANDLE>>						API_GPU_handles;

	//	std::vector<ComPtr<ID3D12Resource>>											UploadBuffers;
};

}