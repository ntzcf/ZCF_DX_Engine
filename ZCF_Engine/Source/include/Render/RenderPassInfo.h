#pragma once

#include "d3dUtil.h"
#include "Scene/SceneManager.h"
#include "Common/DX_Camera.h"
#include "RenderManager.h"
#include "ResAttribute.h"
#include "RenderPSO.h"

//using namespace Engine::Render::resource;

class Engine::Render::FrameGraphicsPassResource;
class Engine::Render::RenderResourceManager;

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
		Lighting,
	};
	//class resource::FrameGraphicsPassResource;
	class Pass_Mat_Info
	{
	public:
		Pass_Mat_Info() {};
		~Pass_Mat_Info() {};

		//	Collect��Ҫ�����ռ�DESC�Ĳ���,��д?
		//virtual void PassCollectBegin();//���ø����ź�,log��,���ڵ���
		//virtual void PassCollect();//�ػ���:����д����ɶ��      ��ͨ��:�������,����ȫҪ�Լ�д,ûʲô����
		//virtual void PassCollectEnd();//ͬBegin

		//virtual void PassExcuteBegin();
		//virtual void PassExcute();
		//virtual void PassExcuteEnd();

		virtual PassInfoType GetPassInfoType() = 0;
		virtual void ExcuteLamda(ID3D12GraphicsCommandList* cmdlist, const FrameGraphicsPassResource& R) = 0;
		virtual std::string GetPassName()=0;

		//							In/Out Buffer,Texture
		//							Resource In CPU
		//							Resource Type, Format,	Usage In Pass
		//							

		//							lamda�ص�����


		//�����β�,ʵ�ζ����ж�̬�ռ�����,�ͼ���,�Զ�����

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

		std::string GetPassName() { return "DepthPass"; }

		void ExcuteLamda(ID3D12GraphicsCommandList* cmdlist, const FrameGraphicsPassResource& R)
		{
			Lamda(cmdlist, R);
		};
	public:
		std::string				PassName;
		std::string				MaterialName;

		resource::RenderPSO				RenderPSO;

		std::function<void(ID3D12GraphicsCommandList*, const FrameGraphicsPassResource&)>				Lamda;
		
		
		//		Queue
		bool					isGraphics;
		//		PSO
		//PSO						PSO;
		//		Resource
		//			VBV			IBV			Position Stream			Index Stream
		//								����ֱ�ӱ��Instance Stream?
		std::unordered_map<resource::ResourceUsage, resource::VertexBuffer>				Vertex_Attribute_Stream;
		std::unordered_map<resource::ResourceUsage, resource::IndexBuffer>				Index_Stream;

		std::unordered_map<resource::ResourceUsage, resource::ResourceInfo>				ResourceInfos;
		
	};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class GBufferPassInfo : public Pass_Mat_Info
	{
	public:
		GBufferPassInfo() {};
		~GBufferPassInfo() {};

		PassInfoType GetPassInfoType() { return PassInfoType::GBuffer; };

		std::string GetPassName() { return "GBufferPass"; }

		void ExcuteLamda(ID3D12GraphicsCommandList* cmdlist, const FrameGraphicsPassResource& R)
		{
			Lamda(cmdlist, R);
		};

		std::string				PassName;
		std::string				MaterialName;

		resource::RenderPSO				RenderPSO;

		std::function<void(ID3D12GraphicsCommandList*, const FrameGraphicsPassResource&)>				Lamda;

		bool					isGraphics;

		//				Position		Normal		Tangent?		UV0			UV1		..............
		std::unordered_map<resource::ResourceUsage, resource::VertexBuffer>				Vertex_Attribute_Stream;
		std::unordered_map<resource::ResourceUsage, resource::IndexBuffer>				Index_Stream;
		//				GBuffer1		GBuffer2		GBuffer3		GBuffer4		GBuffer5
		std::unordered_map<resource::ResourceUsage, resource::ResourceInfo>				Resources;

	};
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class LightingPassInfo : public Pass_Mat_Info
	{
	public:
		LightingPassInfo() {};
		~LightingPassInfo() {};

		std::string				PassName;
		std::string				MaterialName;

		PassInfoType GetPassInfoType() { return PassInfoType::Lighting; };

		std::string GetPassName() { return "LightingPass"; }

		void ExcuteLamda(ID3D12GraphicsCommandList* cmdlist, const FrameGraphicsPassResource& R)
		{
			Lamda(cmdlist, R);
		};

		std::function<void(ID3D12GraphicsCommandList*, const FrameGraphicsPassResource&)>				Lamda;

		bool					isGraphics;

	
		std::string				PassName;
		std::string				MaterialName;

		resource::RenderPSO				RenderPSO;
			//		Compute
		//			IN				OUT:UAV
		std::unordered_map<resource::ResourceUsage, resource::ResourceInfo>								ResourceInofs;

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
			RenderResourceManager,
			Microsoft::WRL::ComPtr<ID3D12Device>)>							Lamda;

		//	Setting?
		
		//			PSO
		//PSO						PSO;
		//  Input		Data		&		Attribute   : 
		std::unordered_map<resource::ResourceUsage, resource::ResourceInfo>								ResourceInofs;
		//	Output		Buffer		Attribute:	Name , Type , Format , Size , ............
		
		//	Queue Type
	};
}