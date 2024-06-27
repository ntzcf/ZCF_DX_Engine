#pragma once
#define TINYOBJLOADER_IMPLEMENTATION 

#include "Scene_Helper.h"

#include "Loader.h"
#include "Materials.h"

namespace Engine::scene::Object
{
	enum class Vertex_Attribute
	{
		Position,
		Normal,
		UV0,
		UV1,

	};

	struct Vertex_Common2_0
	{
		//Vertex_Attribute Position;
		//Vertex_Attribute Normal;
		//Vertex_Attribute UV0;

		uint32_t	Position_Start;
		uint32_t	Position_Lengtn;

		uint32_t	Normal_Start;
		uint32_t	Normal_Length;
		
		uint32_t	UV0_Start;
		uint32_t	UV0_Length;
	};


	class Tiny_OBJ_Object
	{
	public:
		Tiny_OBJ_Object();
		~Tiny_OBJ_Object();

		uint32_t				Material_ID;
		Vertex_Common2_0		Vertex_Attributes;
		uint32_t				Index_Start;
		uint32_t				Index_Length;

	private:


	};



}