#pragma once

#include "SceneObject.h"
#include "Lights.h"
#include "Materials.h"

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

		static std::unordered_map<Object::Vertex_Attribute, std::vector<float>>* GetVAS() {return &Vertex_Attribute_Stream; }
		static std::vector<uint32_t>*				GetIS()		{ return &Index_Stream; };
		static std::vector<Object::Assimp_Object>* GetObjecs()	{ return &Objects; };

		static uint32_t*		GetVertexCommonNums() { return &VertexCommonNums; };
		static uint32_t*		GetIndexNums() { return &IndexNums; };
		static uint32_t*		GetUV_Nums() { return &UV_Nums; };
		
	private:
		//		�������� & ����			�������� & ����		�������� & ����
		//std::vector<Loader::Assimp_Loader>											Assimp_Loaders;
		//std::vector<Loader::Model>													Models;
		Loader::STB_Texture_loader													Tex_Loader;

		//	���Ի���ͳ��������,	Ȼ�����vector.resize(ALL nums);	����ת�����

		static std::vector<Object::Assimp_Object>											Objects;
		static std::unordered_map<Object::Vertex_Attribute , std::vector<float>>			Vertex_Attribute_Stream;
		static std::vector<uint32_t>														Index_Stream;

		std::vector<Materials::CommonMaterial>									Materials;
		std::vector<S_Texture::STB_Texture>										Textures;
		std::vector<Materials::S_Constant>										Constants;

		std::string								ResourceFileDir = "E:/My projects/DX12_Engine/ZCF_Engine/Resources/";
		uint32_t								Tex_nums;
		uint32_t								Mat_nums;

///////	///	///	///	//	�ֶ�ָ��Ҫ���ص�����/////////////////////////////////////////////////////////////
		///////////////	������bindless///////////////////////////////
		///////////// <model Name , Textures Name>//////////
		/////////////<model Name ,  Texture Usage>////////////
		std::unordered_map<std::string, std::vector<std::string>>							TexNames;
		std::unordered_map < std::string, std::vector<Materials::S_Texture_Attribute>>		TexAtts;

///////////////////	///	///////	�ֶ�ָ��Ҫ���ص�ģ��/////////////////////////////////////////////////////
		std::vector<std::string>							ModelNames;
		//std::vector<Object::Vertex_Attribute>				VerAtts;

		static uint32_t										VertexCommonNums;
		static uint32_t										IndexNums;
		static uint32_t										UV_Nums;
	};
}

