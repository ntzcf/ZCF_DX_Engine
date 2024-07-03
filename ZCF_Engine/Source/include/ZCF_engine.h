#pragma once

#include "Headers.hpp"
#include "Common/DX_Camera.h"


class ZCF_Engine
{
public:

	ZCF_Engine(HWND hwnd, UINT width, UINT height);
	~ZCF_Engine();

	bool Init();
	int run();

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void OnMouseDown(WPARAM btnState, int x, int y);

	void OnMouseUp(WPARAM btnState, int x, int y);

	void OnMouseMove(WPARAM btnState, int x, int y);

	void OnKeyboardInput(const Engine::GameLogic::timer::GameTimer& gt);

	static ZCF_Engine* GetEngine() 
	{
		return engine;
	}


private:
	static	ZCF_Engine*											engine;
	HWND														hwnd;
	//GameLogic
	Engine::Common::DX_Camera									mCamera;
	Engine::GameLogic::timer ::GameTimer						mTimer;
	//Scene
	Engine::scene::SceneManager									SceneManager;
	//Render
	Engine::Render::resource::RenderResourceManager				RenderResourceManager;
	Engine::Render::renderer::Renderer							Renderer;
	//std::shared_ptr<Render::frameGraph::RenderFrameGraph>			RFG;










	bool            Paused;
	uint32_t		width;
	uint32_t		height;
	struct CameraPosition
	{
		uint32_t  x;
		uint32_t  y;
	};
	CameraPosition   LastPosition;
	CameraPosition   NowPosition;
};