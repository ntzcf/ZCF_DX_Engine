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
	/// //////////////////////////////////////////	C O M	����ָ�� : ��������ͷŵ�����
	/// </summary>
	
	struct FrameGraphicsPassResource
	{
		//        �Ż���ֱ�Ӹ�handle?  ��RRM��ú���ֱ�Ӱ�handle����,Ȼ��Ԥ��һ��λ��,�Ȼ��չ������ƶ���ȥ.
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>		RTV_Heap;
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
		//		handle / pointer	 RRM::GetXXX(Rname)  { return un_map[name].handle; }

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

		//ͬ����Դ
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
		//		һ��֡һ��Command Queue
		//		һ���߳�һ��Allocator
		//		һ��cmdlist�Ϳ���ͨ����ͬ�ӿڵ��� , �ύ��Queue , Ȼ�����з��͸���Ӧ��Graphic,Compute,Copy����
		//		ͬ��:	֡	��Pass	СPass	�������(��������֮��)
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
	//			��Դ�� --------- Descriptor View ID : �ɸ���
	//		CPU�˿�����ǰ���� , ��ʱ����
		std::unordered_map<uint32_t, ComPtr< D3D12_CPU_DESCRIPTOR_HANDLE>>		API_CPU_handles;
	//		GPU�˵Ļ� , Ҫ����Pass�������������� , ��Ҫ����Ĺ�����
		//			����˼
		std::vector<ComPtr< D3D12_GPU_DESCRIPTOR_HANDLE>>						API_GPU_handles;

	//	std::vector<ComPtr<ID3D12Resource>>											UploadBuffers;
};

}