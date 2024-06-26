#pragma once

#include "SceneObjects.h"
#include "Lights.h"
#include "Materials.h"

namespace Engine::scene::Manager
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


	private:

		std::vector<Object::OBJ_Object>		Primitives;

	};
}

