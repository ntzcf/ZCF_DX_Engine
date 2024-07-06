#pragma once

#include "d3dUtil.h"

namespace Engine::Render::resource::Buffer
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
		Null,
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
		R8_G8_B8_A8

	};

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

		resource::Buffer::ResourceFormat		Foramt;
		resource::Buffer::ResourceType			Type;

		uint32_t								Width;
		uint32_t								Height;

		bool									Frames;
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

		ResourceType			ResourceType{ ResourceType::Vertex };
		
		struct VertexData
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

		};

		static VertexData	GetData() { return VertexData{0}; }

		VertexAttribute			VertexAttribute;
		VertexData				VertexStart;
	};
}
































	 class BaseBuffer
	{
	public:

		BaseBuffer() {};
		~BaseBuffer() {};

		virtual  ResourceType	GetType() = 0;

	};

	class UplaodBuffer :public BaseBuffer
	{

	};

	union Data
	{

		std::vector<float>		VertexData;
		std::vector<uint32_t>	IndexData;
	};
	
	class VertexBuffer :public BaseBuffer
	{
	public:
		VertexBuffer() {};
		~VertexBuffer() {};

		VertexAttribute		GetAttribute() 				{	return	Attribute;	};
		ResourceType		GetType()		override	{	return	Type;};

		std::string				Name;

		VertexAttribute			Attribute;
		
		ResourceType			Type;
		ResourceFormat			Format;


		uint32_t				Size;
		uint32_t				OneBits;
		uint32_t				Nums;

		std::vector<float>		VertexData;
	};

	class IndexBuffer :public BaseBuffer
	{
	public:
		IndexBuffer() {};
		~IndexBuffer() {};

		
		ResourceType		GetType()		override { return	Type; };

		std::string				Name;

		ResourceType			Type;
		ResourceFormat			Format;


		uint32_t				Size;
		uint32_t				OneBits;
		uint32_t				Nums;

		std::vector<uint32_t>		VertexData;
	};


	//class IndexBuffer :public BaseBuffer
	//{
	//public:
	//	IndexBuffer():Type(Index)
	//	{};
	//	~IndexBuffer() {};

	//	std::string				Name;
	//	const ResourceType		Type;
	//	ResourceFormat			Format;

	//	VertexAttribute				Attribute;

	//	uint32_t				Size;
	//	uint32_t				OneBits;
	//	uint32_t				Nums;

	//	Microsoft::WRL::ComPtr<ID3D12Resource>			Resource;

	//};

	//		RTV
	class RenderTargetBuffer :public BaseBuffer
	{
	public:
		RenderTargetBuffer() {};
		~RenderTargetBuffer() {};

		ResourceType		GetType()		override { return	Type; };

		std::string				Name;
		ResourceType			Type;
		ResourceFormat			Format;


		uint32_t				Size;
		uint32_t				OneBits;
		uint32_t				Nums;

		Microsoft::WRL::ComPtr<ID3D12Resource>				Resources;

	};


	//		SOV


	//		CBV
	class ConstantBuffer :public BaseBuffer
	{

	};
	//		Constant--------------Bindless Resource

	//		Instance
	class InstanceBuffer :public BaseBuffer
	{

	};
	//		SRV
	class Texture : public BaseBuffer
	{

	};
 
	//		UAV
	class UAV_Buffer :public BaseBuffer
	{

	};
}