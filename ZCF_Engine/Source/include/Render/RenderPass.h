#pragma once

#include "Helper.h"
#include "Buffer.h"
#include "RenderFrameGraph.h"

namespace Engine::Render::renderpass
{
	//	主要起个收集,记录的作用,叫struct感觉也不错
	//	单Pass,暂没考虑Passes	&	Frames
	//	每个pass都是特化的,有一定假设存在
	//	Pass有大,有小,有工程,有表现,有调试......
	class RenderPassInfo
	{
	public:
		RenderPassInfo() {};
		~RenderPassInfo() {};

		//	Collect主要负责收集DESC的部分,填写?
		virtual void PassCollectBegin();//设置各种信号,log等,便于调试
		virtual void PassCollect();//特化版:这里写假设啥的      普通版:无视这个,基本全要自己写,没什么假设
		virtual void PassCollectEnd();//同Begin

		virtual void PassExcuteBegin();
		virtual void PassExcute();
		virtual void PassExcuteEnd();

	public:
		//	Pass本身
		std::string																						name;
		frameGraph::PassInfo																			PassInfo;
		//	Pass内
		//	PSO								PSO;
		//只能由RFG调用了啊:	Renderer ->	RFG -> RRM ->RFG.Excute
		std::function<void (Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>,
			resource::RenderResourceManager)>			Lamda;
		//	Pass之间	&	Resource封装
		std::vector<frameGraph::RFGResource>															InputResources;
		std::vector<frameGraph::RFGResource>															OutputResources;



		//PSO
		struct RootSignature
		{
			uint16_t	Nums;
			//待定
		};
		struct Shader
		{
			std::string		ShaderPath;
			std::string		ShaderVersion;
			std::string		ShaderMain;
			//使用时候注意;用	string.c_str()	转换
			uint16_t		ShaderFlags1;
			uint16_t		ShaderFlags2;
		};

		struct BlendState
		{

		};




		bool				isStreamOutPut;

		//								PiplineState
		//	形参:PSO
		//	RootSignature	:view形参个数,种类
		//	Shader:		name,	code,	版本
		//	StreamOutput	流输出
		//	BlendState
		//	SampleMask
		//	RasterizerState
		//	DepthStencilState
		//	InputLayout
		//	TopologyType
		//	NumRenderTargets
		//	RTV Formats[8]
		//	DSV Format
		//	SampleDesc
		//	以上这么多的玩意儿,还可以进n步细分,假设,合并:最终优化剩下的才是需要的该Pass形参信息.

		//							In/Out Buffer,Texture
		//							Resource In CPU
		//							Resource Type, Format,	Usage In Pass
		//							

		//							lamda回调函数


		//无论形参,实参都是有动态收集部分,和假设,自动部分
		struct PSO
		{
			RootSignature SG;

		};

	};



	class  LearnPassInfo:public RenderPassInfo
	{
	public:

		LearnPassInfo();
		~LearnPassInfo();

		void PassCollectBegin();
		void PassCollect();
		void PassCollectEnd();

	private:


	};
}