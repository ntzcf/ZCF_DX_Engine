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
		LPI.PassCollect();//	���︺��Ѽ���Ĺ̶�����������
		
		LPI.PassCollectEnd();


		//RFG Pass & Resource Info	-->	RFG	-->	RRM

		//RRM.CreatePassResource(&PassInfo)
		RRM->CreateLearnPassResource(std::move(LPI));
	}
}