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


enum ResourceState
{
	UAV,
	SRV,
	RTV,
	DSV,

};

struct Resource
{
	std::string		name;
	ResourceState	type;
	uint16_t		life;

	uint32_t		id;
};
//type:buffer,texture,Constant...


struct Pass
{
	std::string name;
};

enum PassType
{
	Graphics,
	Compute,
};
	

class RenderFrameGraph
{
public:
	RenderFrameGraph() {};
	~RenderFrameGraph() {};





private:
	std::vector<Pass> Passes;
	std::vector<Resource> Resources;

};
}