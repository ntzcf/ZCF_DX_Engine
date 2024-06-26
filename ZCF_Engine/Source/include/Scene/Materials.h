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
		Albedo,		//		(R,G,B)三原色的反照率
		Normal,
		Metallic,	//		金属度	:	镜面反射 和 漫反射 的强度分配
		Roughness,	//		粗糙度	:	反射花瓣范围,反射纯度		
		Hegiht,
		F0,			//		0°角的Frenel  镜面反射度		漫反射:1-F0	   给电解质:一般0,02 到 0.05 这种变化小的用
					//		或者直接采用真实数据采样
		AO,
		BRDF		//		预计算贴图   (Frenel,Roughness)
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