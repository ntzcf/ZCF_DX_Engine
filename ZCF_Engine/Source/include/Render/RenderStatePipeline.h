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
		//	更多先进的着色器模型
	};

	struct Shader
	{
		ShaderType		ShaderType;
		std::string		ShaderPath;
		std::string		ShaderVersion;
		std::string		ShaderMain;
		//使用时候注意;用	string.c_str()	转换
		uint16_t		ShaderFlags1;
		uint16_t		ShaderFlags2;
	};


	//		Sample	Blend	InputView		Topology	IsStreamOut


	class RenderPSO
	{
		
	};
}