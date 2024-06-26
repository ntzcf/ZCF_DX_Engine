#pragma once
#include <windows.h>
#include <wrl.h>  //添加WTL支持 方便使用COM
#include <wrl/client.h>
#include <strsafe.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <d3d12.h>	//for d3d12
#include <d3d12shader.h>
#include <d3dcompiler.h>
#include <SDKDDKVer.h>
#include <DirectXColors.h>
#define WIN32_LEAN_AND_MEAN // 从 Windows 头中排除极少使用的资料

#if defined(_DEBUG)
#include <dxgidebug.h>
#endif
#include "d3dx12.h"






#include <tchar.h>
#include <pix.h>
#include <memory>
#include <stdint.h>
#include<iostream>
#include <unordered_map>
#include <functional>
#include <optional>






//#if defined(_DEBUG)
//{
//	Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
//	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
//	{
//		debugController->EnableDebugLayer();
//	}
//}
//#endif


// 如果项目处于调试生成阶段，请通过 SDK 层启用调试。
//Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
//if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
//{
//	debugController->EnableDebugLayer();
//}


	// Helper class for COM exceptions
	class com_exception : public std::exception
	{
	public:
		com_exception(HRESULT hr) : result(hr) {}

		const char* what() const noexcept override
		{
			static char s_str[64] = {};
			sprintf_s(s_str, "Failure with HRESULT of %08X",
				static_cast<unsigned int>(result));
			return s_str;
		}

	private:
		HRESULT result;
	};

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw com_exception(hr);
		}
	}

	// 将使用与设备无关的像素(DIP)表示的长度转换为使用物理像素表示的长度。
	inline float ConvertDipsToPixels(float dips, float dpi)
	{
		static const float dipsPerInch = 96.0f;
		return floorf(dips * dpi / dipsPerInch + 0.5f); // 舍入到最接近的整数。
	}

	// 向对象分配名称以帮助调试。
#if defined(_DEBUG)
inline void SetName(ID3D12Object* pObject, LPCWSTR name)
{
	pObject->SetName(name);
}
#else
inline void SetName(ID3D12Object*, LPCWSTR)
{
}
#endif
// 为 ComPtr<T> 命名 helper 函数。
// 将变量名称指定为对象名称。
#define NAME_D3D12_OBJECT(x) SetName(x.Get(), L#x)

