#pragma once
#include "Helper.h"


namespace Engine::Render::frameGraph
{

//前端:各种登记,预创建
//优化:优化图图,决定顺序
//后端:资源创建,并行执行
//				
//						六维条件
// 	   [Pass , Passes]	(PassInfo , ResourceInfo , QueueInfo)
// 



enum RFGResourceType
{
	VertexBuffer,
	IndexBuffer,
	ConstantBuffer,
	InstanceBuffer,
	Texture_2D,
	Texture_3D,
	Texture_Array,
	Sampler,
};

enum RFGResourceFormat
{
	R8_G8_B8_A8
	
};

enum RFGResourceUsage
{
	VBV,
	IBV,
	CBV,
	UAV,
	SOV,
	SRV,
	DSV,
	RTV,
	Sample,
};
//Barrier
struct RFGResource
{
	std::string			name;
	RFGResourceType		Type;
	RFGResourceFormat	Format;
	RFGResourceUsage	Usage;
};



enum PassType
{
	Graphics,
	Compute,
};

struct PassInfo
{
	std::string		name;
	PassType		passType;
};
	

class RenderFrameGraph
{
public:
	RenderFrameGraph() {};
	~RenderFrameGraph() {};





private:

};
}