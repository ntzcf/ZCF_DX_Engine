#pragma once

#include "Scene_Helper.h"

#define TINYOBJLOADER_IMPLEMENTATION 
#include "tinyobjloader-release/tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "assimp/Importer.hpp"      // 导入器在该头文件中定义
#include "assimp/scene.h"           // 读取到的模型数据都放在scene中
#include "assimp/postprocess.h"

#include "Scene/ScenePrimitive.h"
#include <intsafe.h>

using namespace DirectX;


namespace Engine::scene::Loader
{
	//class MyLoader;

	class  Model
	{
	public:
		// load scene for assimp
		Model(const std::string& path , uint32_t UV_nums , std::string  MatID);

		// Traverse and process the nodes in assimp in turn
		void TraverseNode(const aiScene* scene, aiNode* node);

		// load mesh, which includes vertex, index, normal, tangent, texture, material information
		void LoadMesh(const aiScene* scene, aiMesh* mesh);
		//std::vector<uint32_t>				Materials;
		uint32_t							UV_nums;
		std::string 						MatID;
	private:
		std::string directory;

		
		
	};


	/*class Assimp_Loader
	{
	public:
		Assimp_Loader() {};
		~Assimp_Loader() {};

		void LoadModels(std::string FileDir, std::string FileName);

		void TraverseNode(const aiScene* scene, aiNode* node);

	private:
		Assimp::Importer Aip_Importer;

		
	};*/
	//class Tiny_OBJ_Loader
	//{
	//public:

	//	Tiny_OBJ_Loader()
	//	{
	//		reader_config.mtl_search_path = "../../../Resources";
	//	};
	//	~Tiny_OBJ_Loader() {};

	//	//						XXX.obj
	//	void Load_OBJ(std::string FileName) 
	//	{
	//		inputfile = FileName; 
	//		if (!OBJ_Reader.ParseFromFile(inputfile, reader_config)) {
	//			if (!OBJ_Reader.Error().empty()) {
	//				std::cerr << "TinyObjReader: " << OBJ_Reader.Error();
	//			}
	//			exit(1);
	//		}
	//	};

	//	tinyobj::ObjReader			OBJ_Reader;

	//private:


	//	std::string					inputfile ;
	//	tinyobj::ObjReaderConfig	reader_config;
	//	

	//};

}