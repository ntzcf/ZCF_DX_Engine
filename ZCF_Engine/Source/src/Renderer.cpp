#include "Render/Renderer.h"
#include "Render/SrcRenderHelper.h"
#include "Render/RenderPass.h"


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
		LPI.Lamda = [&](const ComPtr<ID3D12GraphicsCommandList> CL,const resource::RenderResourceManager RRM )->void
			{
				CL.BeginPass();
				CL.SetPSO				(RRM.GetPSO("Pname"));
				//vs-ps
				CL.SetVB(RRM.GetVBV("Pname","InR_name"));
				CL.SetIB(RRM.GetIBV("Pname","InR_name"));
				CL.SetViewPort();
				CL.SetScissor();
				CL.SetRenderTargets(Slot,RRM.GetDescriptor("Pname","OutR_name").num, RRM.GetDescroptor("pname","OutR_name").Data);
				CL.ClearRT(...);
				CL.SetDepthStencil(...);
				//Cl.SetDescriptorHeaps();	主动指定,还是自己只指定Descriptor,然后由后端去自行绑定√
				auto SRV = RRM.GetSRV("InR_name", "Pname");
				auto CBV = RRM.GetCBV("InR_name", "Pname");
				auto R1 = RRM.~RenderResourceManager("Rname");
				SRV.GPU_Virtual_Address = R1.GPU_Address;
				//auto UAV相似
				CL.DrawType();
				CL.EndPass();
			};
		
		LPI.PassCollectEnd();


		//RFG Pass & Resource Info	-->	RFG	-->	RRM

		//RRM.CreatePassResource(&PassInfo)
		RRM->CreateLearnPassResource(std::move(LPI));
	}
}