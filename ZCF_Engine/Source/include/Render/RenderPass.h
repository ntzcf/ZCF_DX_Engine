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
		//使用时候注意;用	string.c_str()	转换
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
		//  Poniter  如果资源已存在就有值, 否则置空等分配
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

		//	Collect主要负责收集DESC的部分,填写?
		virtual void PassCollectBegin();//设置各种信号,log等,便于调试
		virtual void PassCollect();//特化版:这里写假设啥的      普通版:无视这个,基本全要自己写,没什么假设
		virtual void PassCollectEnd();//同Begin

		virtual void PassExcuteBegin();
		virtual void PassExcute();
		virtual void PassExcuteEnd();

	public:

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
		//	Pass本身
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