#pragma once

#include "d3dUtil.h"
#include "Scene/SceneManager.h"
#include "Buffer.h"
#include "RenderStatePipeline.h"

//using namespace Engine::Render::resource;

class Engine::Render::resource::FrameGraphicsPassResource;
class Engine::Render::resource::RenderResourceManager;

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

	/// <summary>
	/// //////////////////////////////////////////////////////////////Resource
	/// </summary>
	/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	/// 
	enum PassInfoType
	{
		Depth,
		GBuffer,

	};
	//class resource::FrameGraphicsPassResource;
	class Pass_Mat_Info
	{
	public:
		Pass_Mat_Info() {};
		~Pass_Mat_Info() {};

		//	Collect主要负责收集DESC的部分,填写?
		//virtual void PassCollectBegin();//设置各种信号,log等,便于调试
		//virtual void PassCollect();//特化版:这里写假设啥的      普通版:无视这个,基本全要自己写,没什么假设
		//virtual void PassCollectEnd();//同Begin

		//virtual void PassExcuteBegin();
		//virtual void PassExcute();
		//virtual void PassExcuteEnd();

		virtual PassInfoType GetPassInfoType() = 0;
		virtual void ExcuteLamda(ID3D12GraphicsCommandList* cmdlist, const resource::FrameGraphicsPassResource& R) = 0;
		//virtual std::string Getname();

	public:
		//std::string				Pname;//	Pass
		//std::string				Mname;//	Material

		//bool						isCompute/isGraphics;
		
		//	Setting?
		//			PSO
		//  Input		Data		&		Attribute   : 
		//	Output		Buffer		Attribute:	Name , Type , Format , Size , ............
		//	Queue Type

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
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//class resource::FrameGraphicsPassResource;
	class DepthPassInfo : public Pass_Mat_Info
	{
	public:
		DepthPassInfo() {};
		~DepthPassInfo() {};

		PassInfoType GetPassInfoType() { return PassInfoType::Depth; };

		void ExcuteLamda(ID3D12GraphicsCommandList* cmdlist, const resource::FrameGraphicsPassResource& R)
		{
			Lamda(cmdlist, R);
		};
	public:
		std::string				PassName;
		std::string				MaterialName;

		RenderPSO				RenderPSO;

		std::function<void(ID3D12GraphicsCommandList*, const resource::FrameGraphicsPassResource&)>				Lamda;
		
		
		//		Queue
		bool					isGraphics;
		//		PSO
		//PSO						PSO;
		//		Resource
		//			VBV			IBV			Position Stream			Index Stream
		//								或者直接变成Instance Stream?
		std::unordered_map<resource::Buffer::ResourceInfoUsage, resource::Buffer::VertexBuffer>		Vertex_Attribute_Stream;
		std::unordered_map<resource::Buffer::ResourceInfoUsage, resource::Buffer::IndexBuffer>				Index_Stream;
		
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GBufferPassInfo : public Pass_Mat_Info
	{
	public:
		GBufferPassInfo() {};
		~GBufferPassInfo() {};

		PassInfoType GetPassInfoType() { return PassInfoType::GBuffer; };

		void ExcuteLamda(ID3D12GraphicsCommandList* cmdlist, const resource::FrameGraphicsPassResource& R)
		{
			Lamda(cmdlist, R);
		};

		std::string				PassName;
		std::string				MaterialName;

		std::function<void(ID3D12GraphicsCommandList*, const resource::FrameGraphicsPassResource&)>				Lamda;

		bool					isGraphics;

		//				Position		Normal		Tangent?		UV0			UV1		..............
		std::unordered_map<resource::Buffer::ResourceInfoUsage, resource::Buffer::VertexBuffer>		Vertex_Attribute_Stream;
		std::unordered_map<resource::Buffer::ResourceInfoUsage, resource::Buffer::IndexBuffer>				Index_Stream;
		//				GBuffer1		GBuffer2		GBuffer3		GBuffer4		GBuffer5
		std::unordered_map<resource::Buffer::ResourceInfoUsage, resource::Buffer::ResourceInfo>								ResourceInofs;

	};
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class LightingPassInfo : public Pass_Mat_Info
	{
	public:
		LightingPassInfo() {};
		~LightingPassInfo() {};

		std::string				PassName;
		std::string				MaterialName;

		std::function<void(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>,resource::FrameComputePassResource)>				Lamda;

		bool					isGraphics;
			//		Compute
		//			IN				OUT:UAV
		std::unordered_map<resource::Buffer::ResourceInfoUsage, resource::Buffer::ResourceInfo>								ResourceInofs;

	};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class MaterialPassInfo : public Pass_Mat_Info
	{
	public:
		MaterialPassInfo() {};
		~MaterialPassInfo() {};
	public:
		std::string				PassName;
		std::string				MaterialName;

		bool					isGraphics;

		std::function<void(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>,
			resource::RenderResourceManager,
			Microsoft::WRL::ComPtr<ID3D12Device>)>							Lamda;

		//	Setting?
		
		//			PSO
		//PSO						PSO;
		//  Input		Data		&		Attribute   : 
		std::unordered_map<resource::Buffer::ResourceInfoUsage, resource::Buffer::ResourceInfo>								ResourceInofs;
		//	Output		Buffer		Attribute:	Name , Type , Format , Size , ............
		
		//	Queue Type
	};
}