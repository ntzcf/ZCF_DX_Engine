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

	enum  Texture_Attributes
	{
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

	class Tiny_OBJ_Material
	{
	public:
		Tiny_OBJ_Material();
		~Tiny_OBJ_Material();

	private:

		//PSO	: RootSignature , Shader , Sample , BlendeMode............
		std::unordered_map < Texture_Attributes , S_Texture::Tiny_OBJ_Texture >		Textures;
		
	};

	Tiny_OBJ_Material::Tiny_OBJ_Material()
	{
	}

	Tiny_OBJ_Material::~Tiny_OBJ_Material()
	{
	}

}