#include "ZCF_engine.h"


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

bool InitWindow(HINSTANCE instanceHandle, int show);

int									iWidth = 1024;
int									iHeight = 768;

HWND								hWnd = nullptr;


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int nCmdShow)
{
	MSG									msg = {};
	TCHAR								AppPath[MAX_PATH] = {};


	// 得到当前的工作目录，方便我们使用相对路径来访问各种资源文件
	{
		if (0 == ::GetModuleFileName(nullptr, AppPath, MAX_PATH))
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}

		WCHAR* lastSlash = _tcsrchr(AppPath, _T('\\'));
		if (lastSlash)
		{//删除Exe文件名
			*(lastSlash) = _T('\0');
		}

		lastSlash = _tcsrchr(AppPath, _T('\\'));
		if (lastSlash)
		{//删除x64路径
			*(lastSlash) = _T('\0');
		}

		lastSlash = _tcsrchr(AppPath, _T('\\'));
		if (lastSlash)
		{//删除Debug 或 Release路径
			*(lastSlash + 1) = _T('\0');
		}
	}

	// 创建窗口
	if (!InitWindow(hInstance, nCmdShow))
	{
		return 0;
	}


	try
	{
		ZCF_Engine engine(hWnd,iWidth,iHeight);
		if (!engine.Init())
			return 0;

		return engine.run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}

bool InitWindow(HINSTANCE hInstance, int show)
{

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_GLOBALCLASS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);		//防止无聊的背景重绘
	wcex.lpszClassName = _T("zcf");
	RegisterClassEx(&wcex);

	DWORD dwWndStyle = WS_OVERLAPPED | WS_SYSMENU;
	RECT rtWnd = { 0, 0, iWidth, iHeight };
	AdjustWindowRect(&rtWnd, dwWndStyle, FALSE);

	// 计算窗口居中的屏幕坐标
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
		MessageBox(0, L"CreateWindow FALIED", 0, 0);
		return FALSE;
	}

	ShowWindow(hWnd, show);
	UpdateWindow(hWnd);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	//case WM_KEYDOWN:		//键盘键被按下
	//	if (wParam == VK_ESCAPE)
	//	{
	//		DestoryWindow(g_hMainWnd);
	//		return 0;
	//	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
