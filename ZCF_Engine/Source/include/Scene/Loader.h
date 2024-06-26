#pragma once

#include "Scene_Helper.h"

#define TINYOBJLOADER_IMPLEMENTATION 
#include "tinyobjloader-release/tiny_obj_loader.h"

namespace Engine::scene::Loader
{
	class MyLoader;

	class Tiny_OBJ_Loader
	{
	public:

		Tiny_OBJ_Loader()
		{
			reader_config.mtl_search_path = "../../../Resources";
		};
		~Tiny_OBJ_Loader() {};

		//						XXX.obj
		void Load_OBJ(std::string FileName) 
		{
			inputfile = FileName; 
			if (!OBJ_Reader.ParseFromFile(inputfile, reader_config)) {
				if (!OBJ_Reader.Error().empty()) {
					std::cerr << "TinyObjReader: " << OBJ_Reader.Error();
				}
				exit(1);
			}
		};

	private:

		tinyobj::ObjReader			OBJ_Reader;

		std::string					inputfile ;
		tinyobj::ObjReaderConfig	reader_config;
		

	};
}