#pragma once

#include "Scene_Helper.h"

#define TINYOBJLOADER_IMPLEMENTATION 
#include "tinyobjloader-release/tiny_obj_loader.h"


namespace Engine::scene::S_Texture
{
	class Tiny_OBJ_Texture
	{
	public:
		Tiny_OBJ_Texture();
		~Tiny_OBJ_Texture();

	private:
		
		uint32_t	size;
		tinyobj::material_t* Ting_Material;

	};

	Tiny_OBJ_Texture::Tiny_OBJ_Texture()
	{
	}

	Tiny_OBJ_Texture::~Tiny_OBJ_Texture()
	{
	}

}