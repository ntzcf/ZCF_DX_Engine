#pragma once

#include "Helper.h"
#include "Buffer.h"
#include "Scene/SceneManager.h"

namespace Engine::Render::renderpass
{
	///////////////////////////////////////////////////////PSO
	struct  RootSignature
	{

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
	/// <summary>
	/// //////////////////////////////////////////////////////////////Resource
	/// </summary>
	enum ResourceInfoUsage
	{

		VBV,
		IBV,
		CBV,
		UAV,
		SRV,
		DSV,
		RTV,
		SOV,
		/*Barrier
 		Fence*/
	};

	struct ResourceInfo
	{
		std::string						name;
		//  Poniter  �����Դ�Ѵ��ھ���ֵ, �����ÿյȷ���
		std::optional<std::string>		Data;
		ResourceInfoUsage				Usage;
		//Write   Or   Read
	};

	class resource::RenderResourceManager;


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

	};



	class  LearnPassInfo:public RenderPassInfo
	{
	public:

		LearnPassInfo();
		~LearnPassInfo();

		void PassCollectBegin();
		void PassCollect();
		void PassCollectEnd();

	public:
		//	Pass����
		std::string																						name;
		std::function<void(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>, 
			resource::RenderResourceManager,
			Microsoft::WRL::ComPtr<ID3D12Device>)>														Lamda;
		//	PSO
		//	Resource
		bool																							isStreamOutPut;
		std::vector<ResourceInfo>							InResourceInfos;
		std::vector<ResourceInfo>							OutResourceInfos;
	};
}