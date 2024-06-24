#pragma once
#include "Helper.h"


namespace Engine::Render::frameGraph
{

//ǰ��:���ֵǼ�,Ԥ����
//�Ż�:�Ż�ͼͼ,����˳��
//���:��Դ����,����ִ��
//				
//						��ά����
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