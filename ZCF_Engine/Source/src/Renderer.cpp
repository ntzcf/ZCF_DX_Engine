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
		LPI.PassCollect();//	这里负责把假设的固定部分设置完
		
		LPI.PassCollectEnd();


		//RFG Pass & Resource Info	-->	RFG	-->	RRM

		//RRM.CreatePassResource(&PassInfo)
		RRM->CreateLearnPassResource(std::move(LPI));
	}
}