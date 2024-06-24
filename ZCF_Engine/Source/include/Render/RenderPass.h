#pragma once

#include "Helper.h"
#include "Buffer.h"
#include "RenderFrameGraph.h"

namespace Engine::Render::renderpass
{
	//	��Ҫ����ռ�,��¼������,��struct�о�Ҳ����
	//	��Pass,��û����Passes	&	Frames
	//	ÿ��pass�����ػ���,��һ���������
	//	Pass�д�,��С,�й���,�б���,�е���......
	class RenderPassInfo
	{
	public:
		RenderPassInfo() {};
		~RenderPassInfo() {};

		//	Collect��Ҫ�����ռ�DESC�Ĳ���,��д?
		virtual void PassCollectBegin();//���ø����ź�,log��,���ڵ���
		virtual void PassCollect();//�ػ���:����д����ɶ��      ��ͨ��:�������,����ȫҪ�Լ�д,ûʲô����
		virtual void PassCollectEnd();//ͬBegin

		virtual void PassExcuteBegin();
		virtual void PassExcute();
		virtual void PassExcuteEnd();

	public:
		//	Pass����
		std::string																						name;
		frameGraph::PassInfo																			PassInfo;
		//	Pass��
		//	PSO								PSO;
		//ֻ����RFG�����˰�:	Renderer ->	RFG -> RRM ->RFG.Excute
		std::function<void (Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>,
			resource::RenderResourceManager)>			Lamda;
		//	Pass֮��	&	Resource��װ
		std::vector<frameGraph::RFGResource>															InputResources;
		std::vector<frameGraph::RFGResource>															OutputResources;



		//PSO
		struct RootSignature
		{
			uint16_t	Nums;
			//����
		};
		struct Shader
		{
			std::string		ShaderPath;
			std::string		ShaderVersion;
			std::string		ShaderMain;
			//ʹ��ʱ��ע��;��	string.c_str()	ת��
			uint16_t		ShaderFlags1;
			uint16_t		ShaderFlags2;
		};

		struct BlendState
		{

		};




		bool				isStreamOutPut;

		//								PiplineState
		//	�β�:PSO
		//	RootSignature	:view�βθ���,����
		//	Shader:		name,	code,	�汾
		//	StreamOutput	�����
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
		//	������ô��������,�����Խ�n��ϸ��,����,�ϲ�:�����Ż�ʣ�µĲ�����Ҫ�ĸ�Pass�β���Ϣ.

		//							In/Out Buffer,Texture
		//							Resource In CPU
		//							Resource Type, Format,	Usage In Pass
		//							

		//							lamda�ص�����


		//�����β�,ʵ�ζ����ж�̬�ռ�����,�ͼ���,�Զ�����
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