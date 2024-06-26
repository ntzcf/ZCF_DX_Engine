#pragma once
#include "Helper.h"
#include "Buffer.h"


/// <summary>
/// /////////////////////////////////����:	��	��	д	///////////////////////////////////////////////////////////////
/// </summary>
namespace Engine::Render::frameGraph
{


//						��ά����
// 	   [Pass , Passes]	(PassInfo , ResourceInfo , QueueInfo)
// 

//enum RFGResourceUsage
//{
//	Write,
//	Read,
//	/*VBV,
//	IBV,
//	CBV,
//	UAV,
//	SRV,
//	DSV,
//	RTV,
//	SOV,
//	Sampled,*/
// 	Barrier
// 	Fence
//};
struct RFGResourceInfo
{
	std::string			name;
	//uint16_t			ID;
	uint16_t			Lifes;
	//		resource::Buffer::BaseBuffer* Resource;
	//		����������,��С,������;������
	//		�����Դ�RFG Resource�̳�,�ػ���Դ,���һ������ָ��о���̫�Ȱ�
};



enum class RFGPassQueueType
{
	Graphics,
	Compute,
};

struct RFGPassInfo
{
	std::string							name;
	RFGPassQueueType						QueueType;
	std::vector<RFGResourceInfo>		Reads;
	std::vector<RFGResourceInfo>		Writes;
};
	

class RenderFrameGraph
{
public:
	RenderFrameGraph() {};
	~RenderFrameGraph() {};

	void Add_Pass(RFGPassInfo PI)					{	RFG_PassInfos.emplace	    (PI.name , PI)	;	};
	void Add_Read_Resource(RFGResourceInfo R)		{	RFG_Read_Resources .emplace	( R.name , R )	;	};
	void Add_Write_Resource(RFGResourceInfo R)		{	RFG_Write_Resources.emplace	( R.name , R )	;	};

private:
	std::unordered_map<std::string, RFGPassInfo>			RFG_PassInfos;
	std::unordered_map<std::string, RFGResourceInfo>		RFG_Read_Resources;
	std::unordered_map<std::string, RFGResourceInfo>	    RFG_Write_Resources;
};
}