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

		void LoadObjects();
		void LoadTextures();

	private:
		//		�������� & ����			�������� & ����		�������� & ����
		std::vector<Loader::Tiny_OBJ_Loader>										OBJ_Loaders;
		Loader::STB_Texture_loader													Tex_Loader;

		//	���Ի���ͳ��������,	Ȼ�����vector.resize(ALL nums);	����ת�����

		std::vector<Object::Tiny_OBJ_Object>										Objects;
		std::unordered_map<Object::Vertex_Attribute , std::vector<uint32_t>>		Vertex_Attribute_Stream;
		std::vector<uint32_t>														Index_Stream;

		std::vector<Materials::Tiny_OBJ_Material>									Materials;
		std::vector<S_Texture::Tiny_OBJ_Texture>									Textures;
		std::vector<Materials::S_Constant>											Constants;

	};
}

