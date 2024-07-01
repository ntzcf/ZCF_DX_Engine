#include "d3dUtil.h"

#include "Scene/Materials.h"

namespace Engine::Render::renderpass
{
	using namespace Engine::scene::Materials;
	//				PSO
	enum ShaderType
	{
		VS,
		PS,

		DS,
		HS,
		GS,//	Geometry

		MS,//	Mesh Shader
		
		CS,
		//	�����Ƚ�����ɫ��ģ��
	};

	struct Shader
	{
		ShaderType		ShaderType;
		std::string		ShaderPath;
		std::string		ShaderVersion;
		std::string		ShaderMain;
		//ʹ��ʱ��ע��;��	string.c_str()	ת��
		uint16_t		ShaderFlags1;
		uint16_t		ShaderFlags2;
	};


	//		Sample	Blend	InputView		Topology	IsStreamOut


	class RenderPSO
	{
		
	};
}