#pragma once
#define TINYOBJLOADER_IMPLEMENTATION 

#include "Scene_Helper.h"

#include "SceneLoader.h"

namespace Engine::scene::Primitive
{
	enum class Vertex_Attribute
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

	struct Vertex_Common
	{
		//Vertex_Attribute Position;
		//Vertex_Attribute Normal;
		//Vertex_Attribute BaseColor;

		uint32_t	Position_Start;

		uint32_t	Normal_Start;

		uint32_t	tangent_Start;
	};
	struct Vertex_2DTex
	{
		uint32_t	UV0_Start;
		uint32_t	UV1_Start;
		uint32_t	UV2_Start;
		uint32_t	UV3_Start;
	};


	/*class Tiny_OBJ_Object
	{
	public:
		Tiny_OBJ_Object();
		~Tiny_OBJ_Object();

		uint32_t				Material_ID;
		Vertex_Common			Vertex_Attributes;
		uint32_t				Index_Start;
		uint32_t				Index_Length;

	private:


	};*/

	class Assimp_Primitive
	{
	public:
		Assimp_Primitive	() {};
		~Assimp_Primitive	() {};


		std::vector<std::string>			Materials;
		//Vertex_Common					VertexCommonStart;
		uint32_t						VertexCommonStart;
		Vertex_2DTex					Vertex_2DTex;
		uint32_t						Vertex_Nums;
		//std::vector<Vertex_Attribute>	VetexAttributes;
		uint32_t						Index_Start;
		uint32_t						Index_Length;

	private:

	};



}