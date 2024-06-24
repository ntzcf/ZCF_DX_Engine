#pragma once
#include "Helper.h"


namespace Engine::Render::frameGraph
{

//ǰ��:���ֵǼ�
//�Ż�:�Ż�ͼͼ
//���:�󶨹���
//����:			[name,life] [attribute apiResource]
// 				�������������ְ�,���Ծ�����������Դ
// pass:		[name,input,output,   num,names,type,state,attribute]
// Resource:	[name,type,state,attribute]+ʵ�ʰ󶨵�������Դ����
// ִ��:		passBegin,passExcute,passEnd
//			    ��ʼǰ��������Դ׼����������Դ��,Ȼ��ִ�лص�ʱ��������ȥ����
//				һ��pass����ʱ,�Ϳ��Կ�ʼ׼����һ��pass��,���е�˳��


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