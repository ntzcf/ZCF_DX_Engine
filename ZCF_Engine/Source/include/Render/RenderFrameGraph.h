#pragma once
#include "Helper.h"


namespace Engine::Render::frameGraph
{

//前端:各种登记
//优化:优化图图
//后端:绑定管理
//核心:			[name,life] [attribute apiResource]
// 				生命周期与名字绑定,属性决定真正的资源
// pass:		[name,input,output,   num,names,type,state,attribute]
// Resource:	[name,type,state,attribute]+实际绑定的真正资源索引
// 执行:		passBegin,passExcute,passEnd
//			    开始前给有名资源准备真正的资源绑定,然后执行回调时根据名字去索引
//				一个pass结束时,就可以开始准备下一个pass了,串行的顺序


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
//type:buffer,texture,Constant...



enum PassType
{
	Graphics,
	Compute,
};

struct Pass
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