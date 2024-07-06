#pragma once

#include "Render/d3dUtil.h"
#include "Texture.h"

namespace Engine::Render::resource
{
	//enum Texrure_Attributes
	//{
	//	real_t ambient[3];
	//	real_t diffuse[3];
	//	real_t specular[3];
	//	real_t transmittance[3];
	//	real_t emission[3];

	//};

	//struct Material_Shader
	//{
	//	//ShaderType		ShaderType;
	//	std::string		ShaderPath;
	//	std::string		ShaderName;
	//	std::string		ShaderVersion;
	//	//std::string		ShaderMain;
	//	//ʹ��ʱ��ע��;��	string.c_str()	ת��
	//	//uint16_t		ShaderFlags1;
	//	//uint16_t		ShaderFlags2;
	//};
	/*enum RootParameterType
	{
		ConstantBuffer,
		TextureSRV,
		TextureSampler,
		RootParameterCount,

		UAV,
	};*/

	

	//struct MaterialPSO
	//{
	//	std::vector<Material_Shader>		Shaders;
	//	//std::vector<RootParameterType>		RootParameters;

	//	bool								IsOpacity;
	//};




	enum  class Texture_Attribute
	{
		BaseColor,
		//								Texture					ConstantBuffer					Constant
		//				Pong
		ambient,
		diffuse,
		specular,
		transmittance,
		emission,

		//				PBR
		Albedo,		//		(R,G,B)��ԭɫ�ķ�����
		Normal,
		Metallic,	//		������	:	���淴�� �� ������ ��ǿ�ȷ���
		Roughness,	//		�ֲڶ�	:	���仨�귶Χ,���䴿��		
		Hegiht,
		F0,			//		0��ǵ�Frenel  ���淴���		������:1-F0	   �������:һ��0,02 �� 0.05 ���ֱ仯С����
					//		����ֱ�Ӳ�����ʵ���ݲ���
		AO,
		BRDF		//		Ԥ������ͼ   (Frenel,Roughness)
	};

	/*struct S_Constant
	{
		std::string		name;
		float			Value;
	};*/

	class CommonMaterial
	{
	public:
		CommonMaterial() {};
		~CommonMaterial() {};

		
		std::string													name;

		//MaterialPSO													MP;
		//std::vector<RootParameterType>								RootParameters;
		std::unordered_map < Texture_Attribute ,	std::string >		Textures;
		std::vector<std::string >										ShaderNames;
		bool															IsOpacity;
		//std::unordered_map < std::string		 ,	uint32_t>		Constants;
	private:

		
	};

}