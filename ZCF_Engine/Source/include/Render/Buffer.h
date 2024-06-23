#pragma once

#include "Helper.h"

namespace Engine::Render::resource::Buffer
{
	class   BaseBuffer;
	class	UploadBuffer;
	class	VertexBuffer;
	class	IndexBuffer;
	class	ConstantBuffer;
	class	InstanceBuffer;


	class BaseBuffer
	{
	public:

		BaseBuffer() {};
		~BaseBuffer() {};

	};

	class UplaodBuffer :public BaseBuffer
	{

	};
	class VertexBuffer :public BaseBuffer
	{

	};
	class IndexBuffer :public BaseBuffer
	{

	};
	class ConstantBuffer :public BaseBuffer
	{

	};
	class InstanceBuffer :public BaseBuffer
	{

	};
}