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
		//		�������� & ����			�������� & ����		�������� & ����
		//std::vector<Loader::Assimp_Loader>											Assimp_Loaders;
		//std::vector<Loader::Model>													Models;
		//Loader::STB_Texture_loader													Tex_Loader;

		//	���Ի���ͳ��������,	Ȼ�����vector.resize(ALL nums);	����ת�����

		//	ֱ�����л���Ҳ��
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

///////	///	///	///	//	�ֶ�ָ��Ҫ���ص�ģ�� �� ����/////////////////////////////////////////////////////////////
		///////////////	������bindless///////////////////////////////
		///////////// <model Name , Textures Name>//////////
		/////////////<model Name ,  Texture Usage>////////////
		//std::unordered_map<std::string, std::vector<std::string>>							TexNames;
		//std::unordered_map < std::string, std::vector<Materials::S_Texture_Attribute>>		TexAtts;

///////////////////	///	///////	�ֶ�ָ��Ҫ���ص�ģ��/////////////////////////////////////////////////////
		//std::vector<std::string>							ModelNames;
		//std::vector<Object::Vertex_Attribute>				VerAtts;

		/// <summary>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// </summary>
		///					��Щ num �������� �Լ� ��ֵ�±�
		uint32_t										VertexCommonNums;
		uint32_t										IndexNums;
		uint32_t										UV0_Nums;
		uint32_t										UV1_Nums;
		uint32_t										UV2_Nums;
		uint32_t										UV3_Nums;
	};
}

