#pragma once
#define TINYOBJLOADER_IMPLEMENTATION 

#include "Scene_Helper.h"

#include "Loader.h"
#include "Materials.h"

namespace Engine::scene::Object
{
	class Ting_OBJ_Object
	{
	public:
		Ting_OBJ_Object();
		~Ting_OBJ_Object();

	private:

		//		顶点属性 & 数据			拓扑属性 & 数据		材质属性 & 数据

		Loader::Tiny_OBJ_Loader				Loader;
		Materials::Tiny_OBJ_Material		Material;
	};

	Ting_OBJ_Object::Ting_OBJ_Object()
	{
	}

	Ting_OBJ_Object::~Ting_OBJ_Object()
	{
	}


}