#pragma once

#include "ScenePrimitive.h"

namespace Engine::scene
{


	class SceneManager
	{
	public:
		//static SceneManager& GetSceneManagerInstance ()	noexcept
		//{
		//	static SceneManager  SM;
		//	return SM;
		//}

	public:
		SceneManager() {};
		~SceneManager() {};

		void Init();
		void Update();
		void run();

		void LoadObjects(std::string name , uint32_t UV_Count);
		void LoadTextures(std::string name);

		const std::unordered_map<Object::Vertex_Attribute, std::vector<float>>* GetVAS() {return &Vertex_Attribute_Stream; }
		const std::vector<uint32_t>*				GetIS()		{ return &Index_Stream; };
		const std::vector<Object::Assimp_Primitive>* GetObjecs()	{ return &Primitives; };

		const uint32_t*		GetVertexCommonNums() { return &VertexCommonNums; };
		const uint32_t*		GetIndexNums() { return &IndexNums; };
		const uint32_t*		GetUV0_Nums() { return &UV0_Nums; };
		const uint32_t*		GetUV1_Nums() { return &UV1_Nums; };
		const uint32_t*		GetUV2_Nums() { return &UV2_Nums; };
		const uint32_t*		GetUV3_Nums() { return &UV3_Nums; };
		
	private:
		//		顶点属性 & 数据			拓扑属性 & 数据		材质属性 & 数据
		//std::vector<Loader::Assimp_Loader>											Assimp_Loaders;
		//std::vector<Loader::Model>													Models;
		//Loader::STB_Texture_loader													Tex_Loader;

		//	可以话先统计下数量,	然后调用vector.resize(ALL nums);	减少转移损耗

		//	直接序列化流也行
			std::unordered_map<std::string, std::vector<uint32_t>>						Model_P_IDs;
			std::vector<Object::Assimp_Primitive>										Primitives;
		 
			std::unordered_map<Object::Vertex_Attribute , std::vector<float>>			Vertex_Attribute_Stream;
			std::vector<uint32_t>														Index_Stream;
			std::set<std::string >														MatNames;
		//std::vector<Materials::CommonMaterial>										Materials;
		//std::set<std::string >														Textures;
		//std::vector<S_Texture::STB_Texture>											Textures;
		//std::vector<Materials::S_Constant>										Constants;

		std::string								ResourceFileDir = "E:/My projects/DX12_Engine/ZCF_Engine/Resources/";
		//uint32_t								Tex_nums;
		//uint32_t								Mat_nums;

///////	///	///	///	//	手动指定要加载的模型 和 纹理/////////////////////////////////////////////////////////////
		///////////////	反正有bindless///////////////////////////////
		///////////// <model Name , Textures Name>//////////
		/////////////<model Name ,  Texture Usage>////////////
		//std::unordered_map<std::string, std::vector<std::string>>							TexNames;
		//std::unordered_map < std::string, std::vector<Materials::S_Texture_Attribute>>		TexAtts;

///////////////////	///	///////	手动指定要加载的模型/////////////////////////////////////////////////////
		//std::vector<std::string>							ModelNames;
		//std::vector<Object::Vertex_Attribute>				VerAtts;

		/// <summary>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// </summary>
		///					这些 num 用来计数 以及 赋值下标
		uint32_t										VertexCommonNums;
		uint32_t										IndexNums;
		uint32_t										UV0_Nums;
		uint32_t										UV1_Nums;
		uint32_t										UV2_Nums;
		uint32_t										UV3_Nums;
	};
}

