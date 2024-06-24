#pragma once


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


	private:

	};
}

