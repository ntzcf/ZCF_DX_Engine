#pragma once

#include "Helper.h"

namespace Engine::Render::resource::Buffer
{



	enum class ResourceType
	{
		Null,
		Vertex,
		Index,
		Constant,
		Instance,
		Texture_2D,
		Texture_3D,
		Texture_Array,
		Sampler,

		RenderTarget,
	};

	enum ResourceFormat
	{
		R8_G8_B8_A8

	};

	enum class VertexAttribute
	{
		Index,

		Position,
		Normal,
		UV0,
		UV1,
		UV2,
	};


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


	class V_I_Buffer :public BaseBuffer
	{
	public:
		V_I_Buffer() {};
		~V_I_Buffer() {};

		VertexAttribute		GetAttribute() 				{	return	Attribute;	};
		ResourceType		GetType()		override	{	return	Type;};

		std::string				Name;
		ResourceType			Type;
		ResourceFormat			Format;

		VertexAttribute			Attribute;

		uint32_t				Size;
		uint32_t				OneBits;
		uint32_t				Nums;

		Microsoft::WRL::ComPtr<ID3D12Resource>			Resource;

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
	class UAV_buffer :public BaseBuffer
	{

	};
}