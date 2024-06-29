#pragma once

#include "d3dUtil.h"
#include "Buffer.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneObject.h"

namespace Engine::Render::renderpass
{
	///////////////////////////////////////////////////////PSO
	//		//									ALL_My_Buffer_Resource
	//	//									Graphics
	//std::vector<Buffer::V_I_Buffer>					V_I_Buffers;
	//std::vector<Buffer::InstanceBuffer>				InstanceBuffers;
	////								Texture	+	Constant  ------- Bindless
	//std::vector<Buffer::ConstantBuffer>				ConstantBuffers;
	//std::vector<Buffer::Texture>					Textures;
	////									Compute
	//std::vector<Buffer::UAV_Buffer>					ComputeBuffers;


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

	struct PSO
	{
		Shader				shader;
		RootSignature		RS;
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
		std::string						Data;
		ResourceInfoUsage				Usage;
		//Write   Or   Read
	};

	class resource::RenderResourceManager;


	class Pass_Mat_Info
	{
	public:
		Pass_Mat_Info() {};
		~Pass_Mat_Info() {};

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



	class  LearnPassInfo:public Pass_Mat_Info
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


	class DepthPass : public Pass_Mat_Info
	{
		DepthPass() {};
		~DepthPass() {};

	public:
		std::string				Pname;
		std::string				Mname;
		std::function<void(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>,
			resource::RenderResourceManager,
			Microsoft::WRL::ComPtr<ID3D12Device>)>														Lamda;
		//	PSO
		//	Resource
		bool																							isStreamOutPut;
		std::unordered_map<scene::Object::Vertex_Attribute, resource::Buffer::V_I_Buffer>			Vertex_Attribute_Stream;
		std::unordered_map<scene::Object::Vertex_Attribute, resource::Buffer::V_I_Buffer>			Vertex_Attribute_Stream;
	};

	class MaterialPass : public Pass_Mat_Info
	{
	public:
		MaterialPass() {};
		~MaterialPass() {};
	public:
		std::string				Pname;
		std::string				Mname;
		std::function<void(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>,
			resource::RenderResourceManager,
			Microsoft::WRL::ComPtr<ID3D12Device>)>							Lamda;

		//			PSO
		PSO						PSO;
		//  Input		Data		&		Attribute   : 
		std::unordered_map<scene::Object::Vertex_Attribute, resource::Buffer::Texture>			Texture;
		//	Output		Buffer		Attribute:	Name , Type , Format , Size , ............
		
		//	Setting?
		
		//	Queue Type
	};
}