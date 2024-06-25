#include "Render/Renderer.h"
#include "Render/SrcRenderHelper.h"
#include "Render/RenderPass.h"
#include "Render/RenderResourceManager.h"
#include "Render/Buffer.h"
using namespace resource::Buffer;

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
			std::vector<CD3DX12_CPU_DESCRIPTOR_HANDLE>	RTVs(RTVnums);
			//				handle
			auto handle = ( FGR->RTV_Heap->GetCPUDescriptorHandleForHeapStart());
			//				handle_Start
			auto RTV_size = FGR->RTV_DescriptorSize;
			INT64 RTV_start_Offset = FGR->RTV_StartIndex * RTV_size;
			handle.ptr = SIZE_T(INT64(handle.ptr) + RTV_start_Offset);
			//				RTV_names
			std::vector<std::string > RTV_names(RTVnums);
			RTV_names.push_back( "RenderTarget" );
			//				Handles
			std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> Handles(RTVnums);
			//				loop
			for (int i = 0; i < RTVnums; i++)
			{
				Device->CreateRenderTargetView(FGR->RenderTargets[RTV_names[i]]->Resources.Get(), nullptr, handle);
				Handles.push_back(handle);
				handle.ptr = SIZE_T(INT64(handle.ptr) +RTV_size );
			}
			//				Set
			CL->OMSetRenderTargets(RTVnums, Handles.data(), 1, FGR->DSV);
			

				//CL.BeginPass();
				//CL.SetRenderTargets(RTVs.num(),RTV_Handles.data(),RTVs.Single,FR.DSV);
				//CL.ClearRT(...);
				// 
				// 
				// 
				//auto SRV_Heap=FR.GetSRT_Heap()
				// auto SRs = FR.GetSR(R1name)
				//   for ( R ; SRs )  Device->CreateSRV(SRV_H , R.GPUVirtualAddress) 
				//
				// auto CBV_H = FR.GetCBV_H
				//auto CRs = FR.GetCR("R2name");
				//  for(R:CRs)   Device -> CreateCBV(CBV_H , R.GVA)
				//CL.SetDesciptorHeap(SRV_H   ,  CBV_H );
				//CL.SetDescriptorParemeters( SRV_H.Start ,   CBV_H.Start );
				////UAV相似
				//CL.DrawType();
				//CL.EndPass();
		};
		
		LPI.PassCollectEnd();


		//RFG Pass & Resource Info	-->	RFG	-->	RRM

		//RRM.CreatePassResource(&PassInfo)
		RRM->CreateLearnPassResource(std::move(LPI));
	}
}