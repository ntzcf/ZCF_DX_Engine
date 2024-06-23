#include "zcf_engine.h"



LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int nCmdShow)
{

	int									iWidth = 1024;
	int									iHeight = 768;

	HWND								hWnd = nullptr;
	MSG									msg = {};
	TCHAR								AppPath[MAX_PATH] = {};


	// �õ���ǰ�Ĺ���Ŀ¼����������ʹ�����·�������ʸ�����Դ�ļ�
	{
		if (0 == ::GetModuleFileName(nullptr, AppPath, MAX_PATH))
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}

		WCHAR* lastSlash = _tcsrchr(AppPath, _T('\\'));
		if (lastSlash)
		{//ɾ��Exe�ļ���
			*(lastSlash) = _T('\0');
		}

		lastSlash = _tcsrchr(AppPath, _T('\\'));
		if (lastSlash)
		{//ɾ��x64·��
			*(lastSlash) = _T('\0');
		}

		lastSlash = _tcsrchr(AppPath, _T('\\'));
		if (lastSlash)
		{//ɾ��Debug �� Release·��
			*(lastSlash + 1) = _T('\0');
		}
	}

	// ��������
	{
		WNDCLASSEX wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_GLOBALCLASS;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);		//��ֹ���ĵı����ػ�
		wcex.lpszClassName = _T("zcf");
		RegisterClassEx(&wcex);

		DWORD dwWndStyle = WS_OVERLAPPED | WS_SYSMENU;
		RECT rtWnd = { 0, 0, iWidth, iHeight };
		AdjustWindowRect(&rtWnd, dwWndStyle, FALSE);

		// ���㴰�ھ��е���Ļ����
		INT posX = (GetSystemMetrics(SM_CXSCREEN) - rtWnd.right - rtWnd.left) / 2;
		INT posY = (GetSystemMetrics(SM_CYSCREEN) - rtWnd.bottom - rtWnd.top) / 2;

		hWnd = CreateWindowW(
			_T("zcf")
			, _T("zcf engine")
			, dwWndStyle
			, posX
			, posY
			, rtWnd.right - rtWnd.left
			, rtWnd.bottom - rtWnd.top
			, nullptr
			, nullptr
			, hInstance
			, nullptr);

		if (!hWnd)
		{
			return FALSE;
		}

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}
	ZCF_Engine engine;
	engine.Init(hWnd, iWidth, iHeight);

	while (GetMessage(&msg, NULL, 0, 0) > 0) 
	{
		engine.run();
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	/*HANDLE								hEventFence = nullptr;
	DWORD dwRet = 0;
	BOOL bExit = FALSE;
	SetEvent(hEventFence);*/
	//while (!bExit)
	//{
	//	dwRet = ::MsgWaitForMultipleObjects(1, &hEventFence, FALSE, INFINITE, QS_ALLINPUT);
	//	switch (dwRet - WAIT_OBJECT_0)
	//	{
	//		case 0:	{	engine.run();	}
	//		break;
	//		case 1:
	//		{//������Ϣ
	//			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//			{
	//				if (WM_QUIT != msg.message)
	//				{
	//					::TranslateMessage(&msg);
	//					::DispatchMessage(&msg);
	//				}
	//				else
	//				{
	//					bExit = TRUE;
	//				}
	//			}
	//		}
	//		break;
	//		case WAIT_TIMEOUT:
	//		{

	//		}
	//		break;
	//		default:
	//			break;
	//	}
	//}
	/*catch (com_exception& e)
	{
		e;
	}*/
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
