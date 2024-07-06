#pragma once

#include "d3dUtil.h"
#include "TextureLoader.h"

namespace Engine::Render::resource
{
   /* aiTextureType_NONE = 0,

        aiTextureType_DIFFUSE = 1,
        aiTextureType_SPECULAR = 2,
        aiTextureType_AMBIENT = 3,
        aiTextureType_EMISSIVE = 4,
        aiTextureType_HEIGHT = 5,
        aiTextureType_NORMALS = 6,
        aiTextureType_SHININESS = 7,
        aiTextureType_OPACITY = 8,
        aiTextureType_DISPLACEMENT = 9,
        aiTextureType_LIGHTMAP = 10,
        aiTextureType_REFLECTION = 11,
        aiTextureType_BASE_COLOR = 12,
        aiTextureType_NORMAL_CAMERA = 13,
        aiTextureType_EMISSION_COLOR = 14,
        aiTextureType_METALNESS = 15,
        aiTextureType_DIFFUSE_ROUGHNESS = 16,
        aiTextureType_AMBIENT_OCCLUSION = 17,
        aiTextureType_SHEEN = 19,
        aiTextureType_CLEARCOAT = 20,
        aiTextureType_TRANSMISSION = 21,

      aiTextureType_UNKNOWN = 18,*/

	class STB_Texture
	{
	public:
		STB_Texture() {};
		~STB_Texture() { stbi_image_free(Texture_Data); };


		std::string		name;
		int	        	x;
		int	        	y;
		int	        	size;
		//Data
		unsigned char*	Texture_Data;
	private:
		

	};

}