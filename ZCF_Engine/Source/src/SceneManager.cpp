#include "Scene/SceneManager.h"
#include "Render/SrcRenderHelper.h"


using namespace Engine::scene::Object;

namespace Engine::scene
{
	void SceneManager::Init()
	{
		LoadObjects();

	}

	void SceneManager::Update()
	{

	}

	void SceneManager::run()
	{

	}

	void SceneManager::LoadObjects(std::string name , uint32_t UV_Count)
	{
		
		Materials::CommonMaterial  CM;
		CM.name = name+".Material";

		int num = TexNames[name].size();
		auto Tex		= TexNames[name];
		auto TexAtt		= TexAtts[name];

		for (int i = 0; i < num; i++)
		{

			CM.Textures.emplace(TexAtt[i], Tex_nums++);
			LoadTextures(Tex[i]);
		}

		Materials.push_back(std::move(CM));

		Loader::Model model(ResourceFileDir + name, UV_Count ,Mat_nums++);
		//model.Materials.push_back(Mat_nums++);

		//Models.push_back(std::move(model));

		//int MatSize = model.Materials.size();
		//int VerAttSize = VerAtts.size();

	}

	void SceneManager::LoadTextures(std::string name)
	{
		S_Texture::STB_Texture	Texture;
		Texture.name = name;
		int n;
		Texture.Texture_Data=Tex_Loader.LoadTexture((ResourceFileDir + name).c_str(),&Texture.x,&Texture.y,&n,0);
		Textures.push_back(std::move(Texture));

	}























}