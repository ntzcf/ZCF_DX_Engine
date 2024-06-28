#pragma once

#include "Scene_Helper.h"
#include "S_Texture.h"

namespace Engine::scene::Materials
{
	//enum Texrure_Attributes
	//{
	//	real_t ambient[3];
	//	real_t diffuse[3];
	//	real_t specular[3];
	//	real_t transmittance[3];
	//	real_t emission[3];

	//};

	enum  class S_Texture_Attribute
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

	struct S_Constant
	{
		std::string		name;
		float			Value;
	};

	class CommonMaterial
	{
	public:
		CommonMaterial() {};
		~CommonMaterial() {};


		std::string													name;
		std::unordered_map < S_Texture_Attribute ,	uint32_t>		Textures;
		std::unordered_map < std::string		 ,	uint32_t>		Constants;
		//PSO	: RootSignature , Shader , Sample , BlendeMode............
	private:

		
	};

}