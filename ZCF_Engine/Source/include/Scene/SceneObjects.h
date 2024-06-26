#pragma once
#define TINYOBJLOADER_IMPLEMENTATION 

#include "Scene_Helper.h"

#include "Loader.h"
#include "Materials.h"

namespace Engine::scene::Object
{
	class OBJ_Object
	{
	public:
		OBJ_Object();
		~OBJ_Object();

	private:

		Loader::Tiny_OBJ_Loader		Loader;
		Materials::PBR_Materials	Materials;
	};

	OBJ_Object::OBJ_Object()
	{
	}

	OBJ_Object::~OBJ_Object()
	{
	}


}