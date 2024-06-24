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
		//��ִ֡��ͼ����clearΪ��֡�ռ�ͼ
		//RFG = RFGs[frameCount % 2].get.reset();
	}
	void Renderer::RenderEnd()
	{
		//Fence:�ȱ�ִ֡��ͼ
		// �����߳���ͼ
		//����:��֡���ռ�ͼ��ʼ����;
		// ��дһ��lamada,�����Լ���,����End����Χ�� ע:�ռ�ͼ��Ϊ��					���ñ���ִ���߳�
		//Present:�ϴ�������
	}
	void Renderer::LearnPass()
	{
		renderpass::LearnPassInfo LPI;
		LPI.PassCollectBegin();
		LPI.PassCollect();//	���︺��Ѽ���Ĺ̶�����������?
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
				//Cl.SetDescriptorHeaps();	����ָ��,�����Լ�ָֻ��Descriptor,Ȼ���ɺ��ȥ���а󶨡�
				auto SRV = RRM.GetSRV("InR_name", "Pname");
				auto CBV = RRM.GetCBV("InR_name", "Pname");
				auto R1 = RRM.~RenderResourceManager("Rname");
				SRV.GPU_Virtual_Address = R1.GPU_Address;
				//auto UAV����
				CL.DrawType();
				CL.EndPass();
			};
		
		LPI.PassCollectEnd();


		//RFG Pass & Resource Info	-->	RFG	-->	RRM

		//RRM.CreatePassResource(&PassInfo)
		RRM->CreateLearnPassResource(std::move(LPI));
	}
}