#pragma once

#include "Headers.hpp"


class ZCF_Engine
{
public:
	ZCF_Engine();
	~ZCF_Engine();

	void Init(HWND hwnd, UINT width, UINT height);
	void run();


private:
	//GameLogic
	Engine::GameLogic::camera::DX_Camera						Camera;
	Engine::GameLogic::timer ::GameTimer						Timer;
	//Scene
	Engine::scene::SceneManager									SceneManager;
	//Render
	Engine::Render::resource::RenderResourceManager				RenderResourceManager;
	Engine::Render::renderer::Renderer							Renderer;
	//std::shared_ptr<Render::frameGraph::RenderFrameGraph>			RFG;
};