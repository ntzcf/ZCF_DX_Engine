#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"	

class STB_Texture_loader
{
public:
	STB_Texture_loader() {};
	~STB_Texture_loader() {};

	unsigned char* LoadTexture(char const* filename, int* x, int* y, int* channels_in_file, int desired_channels)
	{
		return stbi_load(filename, x, y, channels_in_file, desired_channels);
	}

private:

};