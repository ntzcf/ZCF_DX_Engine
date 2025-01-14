#include "ZCF_engine.h"
#include <WindowsX.h>

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return ZCF_Engine::GetEngine()->MsgProc(hwnd, msg, wParam, lParam);
}

using namespace Engine;

ZCF_Engine::ZCF_Engine(HWND hwnd, UINT width, UINT height):hwnd(hwnd),width(width),height(height)
{
}

ZCF_Engine::~ZCF_Engine()
{
}

bool ZCF_Engine::Init()
{
	//GameLogic.Init();
	//scene.Init();
	SceneManager.Init();//Setting ;  Load_Asset in cpu
	
	//render.Init();
	RenderResourceManager.Init(hwnd, width, height);//Setting ; Device and Window Dependent Resource  and runtime Resource.
	Renderer.Init(&SceneManager);//	Setting ; RFG ; 
}

int ZCF_Engine::run()
{
		MSG msg = { 0 };

		mTimer.Reset();

		while (msg.message != WM_QUIT)
		{
			// If there are Window messages then process them.
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// Otherwise, do animation/game stuff.
			else
			{
				mTimer.Tick();

				if (!Paused)
				{
					SceneManager.Update();
					RenderResourceManager.Update();
					Renderer.Update();

					//run
					SceneManager.run();
					Renderer.run();
					RenderResourceManager.run();
				}
				else
				{
					Sleep(100);
				}
			}
		}
		return (int)msg.wParam;
}

LRESULT  ZCF_Engine::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	//case WM_ACTIVATE:
	//	if (LOWORD(wParam) == WA_INACTIVE)
	//	{
	//		mAppPaused = true;
	//		mTimer.Stop();
	//		
	//	}
	//	else
	//	{
	//		mAppPaused = false;
	//		mTimer.Start();
	//	}
	//	return 0;

	//	// WM_SIZE is sent when the user resizes the window.  
	//case WM_SIZE:
	//	// Save the new client area dimensions.
	//	mClientWidth = LOWORD(lParam);
	//	mClientHeight = HIWORD(lParam);
	//	if (md3dDevice)
	//	{
	//		if (wParam == SIZE_MINIMIZED)
	//		{
	//			mAppPaused = true;
	//			mMinimized = true;
	//			mMaximized = false;
	//		}
	//		else if (wParam == SIZE_MAXIMIZED)
	//		{
	//			mAppPaused = false;
	//			mMinimized = false;
	//			mMaximized = true;
	//			OnResize();
	//		}
	//		else if (wParam == SIZE_RESTORED)
	//		{

	//			// Restoring from minimized state?
	//			if (mMinimized)
	//			{
	//				mAppPaused = false;
	//				mMinimized = false;
	//				OnResize();
	//			}

	//			// Restoring from maximized state?
	//			else if (mMaximized)
	//			{
	//				mAppPaused = false;
	//				mMaximized = false;
	//				OnResize();
	//			}
	//			else if (mResizing)
	//			{
	//				// If user is dragging the resize bars, we do not resize 
	//				// the buffers here because as the user continuously 
	//				// drags the resize bars, a stream of WM_SIZE messages are
	//				// sent to the window, and it would be pointless (and slow)
	//				// to resize for each WM_SIZE message received from dragging
	//				// the resize bars.  So instead, we reset after the user is 
	//				// done resizing the window and releases the resize bars, which 
	//				// sends a WM_EXITSIZEMOVE message.
	//			}
	//			else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
	//			{
	//				OnResize();
	//			}
	//		}
	//	}
	//	return 0;

	//	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	//case WM_ENTERSIZEMOVE:
	//	mAppPaused = true;
	//	mResizing = true;
	//	mTimer.Stop();
	//	return 0;

	//	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	//	// Here we reset everything based on the new window dimensions.
	//case WM_EXITSIZEMOVE:
	//	mAppPaused = false;
	//	mResizing = false;
	//	mTimer.Start();
	//	OnResize();
	//	return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		//else if ((int)wParam == VK_F2)
			//Set4xMsaaState(!m4xMsaaState);

		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void ZCF_Engine::OnMouseDown(WPARAM btnState, int x, int y)
{
	LastPosition.x = x;
	LastPosition.y = y;

	SetCapture(hwnd);
}

void  ZCF_Engine::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void  ZCF_Engine::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - LastPosition.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - LastPosition.y));

		mCamera.Pitch(dy);
		mCamera.Yaw(dx);
	}

	LastPosition.x = x;
	LastPosition.y = y;
}

void ZCF_Engine::OnKeyboardInput(const Engine::GameLogic::timer::GameTimer& gt)
{
	const float dt = gt.DeltaTime();

	if (GetAsyncKeyState('W') & 0x8000)
		mCamera.Walk(10.0f * dt);

	if (GetAsyncKeyState('S') & 0x8000)
		mCamera.Walk(-10.0f * dt);

	if (GetAsyncKeyState('A') & 0x8000)
		mCamera.Strafe(-10.0f * dt);

	if (GetAsyncKeyState('D') & 0x8000)
		mCamera.Strafe(10.0f * dt);

	mCamera.UpdateViewMatrix();
}
