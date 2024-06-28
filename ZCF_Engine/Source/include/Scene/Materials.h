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