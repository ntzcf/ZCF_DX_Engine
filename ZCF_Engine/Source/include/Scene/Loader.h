#pragma once

#include "Scene_Helper.h"

#define TINYOBJLOADER_IMPLEMENTATION 
#include "tinyobjloader-release/tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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

		tinyobj::ObjReader			OBJ_Reader;

	private:


		std::string					inputfile ;
		tinyobj::ObjReaderConfig	reader_config;
		

	};

	class STB_Texture_loader
	{
	public:
		STB_Texture_loader();
		~STB_Texture_loader();

		unsigned char* LoadTexture(char const* filename, int* x, int* y, int* channels_in_file, int desired_channels)
		{
			return stbi_load( filename,  x, y,  channels_in_file, desired_channels);
		}

	private:

	};

	STB_Texture_loader::STB_Texture_loader()
	{
	}

	STB_Texture_loader::~STB_Texture_loader()
	{
	}
}