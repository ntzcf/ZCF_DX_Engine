#include "Render/Renderer.h"
#include "Render/SrcRenderHelper.h"
#include "Render/RenderPass.h"
#include "Render/RenderResourceManager.h"
#include "Render/Buffer.h"
#include "Render/RenderFrameGraph.h"

using namespace resource::Buffer;
using namespace frameGraph;
using namespace renderpass;

namespace Engine::Render::renderer
{
	void Renderer::Init()
	{
	}
	void Renderer::Update()
	{
	}
	void Renderer::run()
	{
		RenderBegin();
		Render();
		RenderEnd();
	}
	void Renderer::Render()
	{
		LearnPass();
	}
	void Renderer::RenderBegin()
	{
		//上帧执行图重置clear为本帧收集图
		//RFG = RFGs[frameCount % 2].get.reset();
	}
	void Renderer::RenderEnd()
	{
		//Fence:等本帧执行图
		// 回收线程与图
		//编译:本帧的收集图开始编译;
		// 编写一个lamada,让它自己跑,反正End里有围栏 注:收集图不为空					重用编译执行线程
		//Present:上传交换链
	}
	void Renderer::LearnPass()
	{
		renderpass::LearnPassInfo LPI;
		LPI.PassCollectBegin();
		LPI.PassCollect();//	这里负责把假设的固定部分设置完?
		LPI.Lamda=[&](Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CL, resource::RenderResourceManager RRM,
			Microsoft::WRL::ComPtr<ID3D12Device> Device)->void
		{
			auto FGR = RRM.GetFrameGraphicsResource("LearnPass");

///////////////////////////////////////////////////////////////    PSO
			CL->SetPipelineState(FGR->PSO.Get());
			
////////////////////////////////////////////////////////////////	Vertex_Index_buffers
			std::vector<D3D12_VERTEX_BUFFER_VIEW>  VBVs;
			std::vector<D3D12_INDEX_BUFFER_VIEW>   IBVs;

			for (auto VIB : FGR->V_I_Buffers)
			{
				if (VIB->GetAttribute() == VertexAttribute::Index)
				{
					D3D12_INDEX_BUFFER_VIEW IBV;
					IBV.BufferLocation	=	VIB->Resource.Get()->GetGPUVirtualAddress();
					IBV.SizeInBytes		=	VIB->Size / 8;
					IBV.Format			=	VIB->Nums > 65536?  DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
					IBVs.push_back(std::move(IBV));
				}
				else
				{
					D3D12_VERTEX_BUFFER_VIEW VBV;
					VBV.BufferLocation = VIB->Resource.Get()->GetGPUVirtualAddress();
					VBV.SizeInBytes = VIB->Size / 8;
					VBV.StrideInBytes = VIB->OneBits/8;
					VBVs.push_back(std::move(VBV));
				}
			}
			//           这个输入槽Slot  得与PSO中InputLayput设置一样才行啊 , 这种循环法还得改进.
			//           可以改下循环, 比如固定Position走开始slotS ,  Normal走slotS+1 ,   UV0走号slotS+2
			//           记下一个开始slot,  假定输入slot都是连续的
			//			 把绑定给移到循环里.
			CL->IASetVertexBuffers(0,VBVs.size(),VBVs.data());
			CL->IASetIndexBuffer(IBVs.data());
			//			IndexBuffer好像固定只有一个,没必要vector的
/////////////////////////////////////////////////////////	Topology


////////////////////////////////////////////////////////	ViewPort


///////////////////////////////////////////////////////		Scissor

//////////////////////////////////////////////////////		RTV
			//				num 
			auto RTVnums = FGR->RenderTargets.size();
			//				handle
			auto handle = ( FGR->RTV_Heap->GetCPUDescriptorHandleForHeapStart());
			//				handle_Start
			auto RTV_size = FGR->RTV_DescriptorSize;
			INT64 RTV_start_Offset = FGR->RTV_StartIndex * RTV_size;
			handle.ptr = SIZE_T(INT64(handle.ptr) + RTV_start_Offset);
			//				RTVs
			std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>	RTVs(RTVnums);
			//				RTV_names
			std::vector<std::string > RTV_names(RTVnums);
			RTV_names.push_back( "RenderTarget" );
			//				loop
			for (int i = 0; i < RTVnums; i++)
			{
				Device->CreateRenderTargetView(FGR->RenderTargets[RTV_names[i]]->Resources.Get(), nullptr, handle);
				RTVs.push_back(handle);
				CL->ClearRenderTargetView(handle, 0, 0, nullptr);
				handle.ptr = SIZE_T(INT64(handle.ptr) +RTV_size );
			}
			//             DSV
			CL->ClearDepthStencilView(*(FGR->DSV), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

			//			Set
			CL->OMSetRenderTargets(RTVnums, RTVs.data(), 1, FGR->DSV);
			
////////////////////////////////////////////////	CBV  SRV	Constant
//			
				//CL.BeginPass();
				//CL.SetDesciptorHeap(SRV_H   ,  CBV_H );
				//CL.SetDescriptorParemeters( SRV_H.Start ,   CBV_H.Start );
				////UAV相似
				//CL.DrawType();
				//CL.EndPass();
		};	
		LPI.PassCollectEnd();

////////////////////////////////////////////////////////////////RFG

		frameGraph::RenderFrameGraph RFG;

		frameGraph::RFGPassInfo			Pass;
		Pass.name = "LearnPass";
		Pass.QueueType = frameGraph::RFGPassQueueType::Graphics;
		
		int size = LPI.InResourceInfos.size();
		for (int i = 0; i < size; i++)
		{
			frameGraph::RFGResourceInfo RI;
			RI.name = LPI.InResourceInfos[i].name;
			RFG.Add_Read_Resource(RI);
			Pass.Reads.push_back(std::move(RI));
		}

		size = LPI.OutResourceInfos.size();
		for (int i = 0; i < size; i++)
		{
			frameGraph::RFGResourceInfo RI;
			RI.name = LPI.OutResourceInfos[i].name;
			RFG.Add_Write_Resource(RI);
			Pass.Writes.push_back(std::move(RI));
		}

		RFG.Add_Pass(std::move(Pass));

		//		还要管理资源,和Pass的具体内部信息,	裁剪时可以选择少发送一些请求.
		//		好麻烦啊啊啊

		//		RFG的整合(预创建对象,同步对象),编译,执行
		//		统一执行, 局部独立执行
		//		全局对象注册............
	}
}