#include "Render/ResAttribute.h"

namespace Engine::Render::resource
{

	DXGI_FORMAT		Get_DXGI_Format(ResourceFormat format)
	{
		if (format == ResourceFormat::Format_D24_UNORM_S8_UINT)
		{
			return  DXGI_FORMAT_D24_UNORM_S8_UINT;
		}
		if(format == ResourceFormat::RGBA_32_FLOAT)
		{
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	};
}