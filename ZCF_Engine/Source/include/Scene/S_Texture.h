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


		std::string		name;
		uint32_t		size;
		//Data
		std::vector<uint32_t>	Texture_Data;
	private:
		

	};

	Tiny_OBJ_Texture::Tiny_OBJ_Texture()
	{
	}

	Tiny_OBJ_Texture::~Tiny_OBJ_Texture()
	{
	}

}