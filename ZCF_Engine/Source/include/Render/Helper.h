#pragma once
#include <windows.h>
#include <wrl.h>  //���WTL֧�� ����ʹ��COM
#include <wrl/client.h>
#include <strsafe.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <d3d12.h>	//for d3d12
#include <d3d12shader.h>
#include <d3dcompiler.h>
#include <SDKDDKVer.h>
#include <DirectXColors.h>
#define WIN32_LEAN_AND_MEAN // �� Windows ͷ���ų�����ʹ�õ�����

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


// �����Ŀ���ڵ������ɽ׶Σ���ͨ�� SDK �����õ��ԡ�
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

	// ��ʹ�����豸�޹ص�����(DIP)��ʾ�ĳ���ת��Ϊʹ���������ر�ʾ�ĳ��ȡ�
	inline float ConvertDipsToPixels(float dips, float dpi)
	{
		static const float dipsPerInch = 96.0f;
		return floorf(dips * dpi / dipsPerInch + 0.5f); // ���뵽��ӽ���������
	}

	// �������������԰������ԡ�
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
// Ϊ ComPtr<T> ���� helper ������
// ����������ָ��Ϊ�������ơ�
#define NAME_D3D12_OBJECT(x) SetName(x.Get(), L#x)

