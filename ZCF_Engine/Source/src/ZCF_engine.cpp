#include "ZCF_engine.h"

using namespace Engine;

ZCF_Engine::ZCF_Engine()
{
}

ZCF_Engine::~ZCF_Engine()
{
}

void ZCF_Engine::Init(HWND hwnd , UINT width , UINT height)
{
	//GameLogic.Init();
	//scene.Init();
	SceneManager.Init();//Setting ;  Load_Asset in cpu
	
	//render.Init();
	RenderResourceManager.Init(hwnd, width, height);//Setting ; Device and Window Dependent Resource  and runtime Resource.
	Renderer.Init();//	Setting ; RFG ; 
	Renderer.RRM = &RenderResourceManager;
}

void ZCF_Engine::run()
{
	//Update
	SceneManager.Update();
	RenderResourceManager.Update();
	Renderer.Update();

	//run
	SceneManager.run();
	RenderResourceManager.run();
	Renderer.run();

}
