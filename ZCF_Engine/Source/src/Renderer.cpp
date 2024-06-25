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
				////UAV����
				//CL.DrawType();
				//CL.EndPass();
		};
		
		LPI.PassCollectEnd();


		//RFG Pass & Resource Info	-->	RFG	-->	RRM

		//RRM.CreatePassResource(&PassInfo)
		RRM->CreateLearnPassResource(std::move(LPI));
	}
}