#include "Render/Renderer.h"
#include "Render/SrcRenderHelper.h"
#include "Render/RenderPass.h"
#include "Render/RenderResourceManager.h"


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

			
			CL->SetPipelineState(RRM.GetPSO(LPI.name));

			CL->IASetVertexBuffers(0,1,RRM.GetVBV(LPI.name));

			CL->OMSetRenderTargets(3,RRM.GetRTVs);




				//CL.BeginPass();
				//auto FR = RRM.GetFrameResource("Pname");
				////vs-ps
				//CL.SetVB(FR.GetVBV);
				//CL.SetIB(RRM.GetIBV);
				//CL.SetViewPort(FR.ViewPort);
				//CL.SetScissor(FR.Scissor);
				//auto RTVs = FR.RTVs
				//		RTV_Handles[RTVs.num()];
				//		int i=0;
				//for (auto RTV : FR.RTVs)
				// {
				//		RTV_Handles[i++]=RTV.handle
				// }
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