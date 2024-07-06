#pragma once

#include "d3dUtil.h"

namespace Engine::Render::resource
{


	enum class ResourceUsage
	{

		VBV,
		IBV,
		CBV,
		RCV,//		Root Constant Value(View)
		SRV,
		DSV,
		RTV,

		UAV,

		//SOV,
		/*Barrier
		Fence*/
	};


	enum class ResourceType
	{
		null,
		Vertex,
		Index,

		Instance,

		Root_Constant,

		Constant_Buffer,
		Structure_Buffer,

		Texture_2D,
		Texture_3D,
		Texture_Array,

		Sampler,
	};

	enum class ResourceFormat
	{
		null,
		RGBA_32_FLOAT,
		R8_G8_B8_A8,
		Format_D24_UNORM_S8_UINT,

	};
	DXGI_FORMAT			Get_DXGI_Format(ResourceFormat format);

	enum class VertexAttribute
	{
		Position,
		Normal,
		tangent,
		BaseColor,
		UV0,
		UV1,
		UV2,
		UV3,
	};


	struct ResourceInfo
	{
		std::string								name;

		resource::ResourceFormat		Foramt=ResourceFormat::null;
		resource::ResourceType			Type=ResourceType::null;

		uint32_t								Width=0;
		uint32_t								Height=0;

		bool									Global = 1;
		//		如何针对不同种类: Texture , RootConstant , ConstantBuffer , Sampler?
		//		让Renderer去统计然后全部上传.
		//		最终靠名字去索引就完了.
	};

	class RenderResourceType
	{
	public:

		RenderResourceType() {};
		virtual ~RenderResourceType() {};

		virtual ResourceType GetResourceType() = 0;

	};

	class VertexBuffer : public RenderResourceType
	{
	public:
		VertexBuffer() {};
		~VertexBuffer() {};

		virtual ResourceType GetResourceType() { return ResourceType; };
		
		VertexAttribute	  GetVertexAttribute() { return VertexAttribute; };

		ResourceType			ResourceType{ ResourceType::Vertex };
		
		VertexAttribute			VertexAttribute;
		uint32_t				Offset;
		uint32_t				OneBits;
		uint32_t				num;
		/*struct VertexData
		{
			uint32_t                PostionStart;
			uint32_t				NormalStart;
			uint32_t				TangentStart;
			uint32_t				BaseColorStart;

			uint32_t				UV0Start;
			uint32_t				UV1Start;
			uint32_t				UV2Start;
			uint32_t				UV3Start;

			uint32_t				num;

		};*/

		//static VertexData	GetData() { return VertexData{0}; }

		//VertexData				VertexStart;
	};

	class IndexBuffer : public RenderResourceType
	{
	public:
		IndexBuffer() {};
		~IndexBuffer() {};

		virtual ResourceType GetResourceType() { return ResourceType; };

		ResourceType			ResourceType{ ResourceType::Index };

		uint32_t				Offset;
		uint32_t				OneBits;
		uint32_t				num;
	};

	class ConstantBuffer : public RenderResourceType
	{
	public:
		ConstantBuffer() {};
		~ConstantBuffer() {};

		virtual ResourceType GetResourceType() { return ResourceType; };

		ResourceType			ResourceType{ ResourceType::Constant_Buffer };
	};

	class StructureBuffer : public RenderResourceType
	{
	public:
		StructureBuffer() {};
		~StructureBuffer() {};

		virtual ResourceType GetResourceType() { return ResourceType; };

		ResourceType			ResourceType{ ResourceType::Structure_Buffer };
	};

	
}







