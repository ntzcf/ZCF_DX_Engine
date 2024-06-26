#pragma once

#include "Scene_Helper.h"
#include "S_Texture.h"

namespace Engine::scene::Materials
{
	//enum  RBR_Texture_Attributes
	//{
	//	Albedo,		//		(R,G,B)��ԭɫ�ķ�����
	//	Normal,
	//	Metallic,	//		������	:	���淴�� �� ������ ��ǿ�ȷ���
	//	Roughness,	//		�ֲڶ�	:	���仨�귶Χ,���䴿��		
	//	Hegiht,
	//	F0,			//		0��ǵ�Frenel  ���淴���		������:1-F0	   �������:һ��0,02 �� 0.05 ���ֱ仯С����
	//				//		����ֱ�Ӳ�����ʵ���ݲ���
	//	AO,
	//	BRDF		//		Ԥ������ͼ   (Frenel,Roughness)
	//};

	class PBR_Materials
	{
	public:
		PBR_Materials();
		~PBR_Materials();

	private:

		//PSO	: RootSignature , Shader , Sample , BlendeMode............
		std::unordered_map<Texture::RBR_Texture_Attributes, Texture>		Textures;
		
	};

	PBR_Materials::PBR_Materials()
	{
	}

	PBR_Materials::~PBR_Materials()
	{
	}

}