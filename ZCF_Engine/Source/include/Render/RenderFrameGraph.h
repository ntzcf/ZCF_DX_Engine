#pragma once
#include "d3dUtil.h"
#include "Buffer.h"
#include "RenderPass.h"

#include <bitset>

/// <summary>
/// /////////////////////////////////����:	��	��	д	///////////////////////////////////////////////////////////////
/// </summary>
namespace Engine::Render::frameGraph
{
	struct RFGPassInfo;

//						8ά����
// 	   [Pass , Passes]	(PassInfo , ResourceInfo , QueueInfo , ResourceState(Barrier))
// 
enum class RFGPassQueueType
{
	Graphics,
	Compute,
	//Copy,
	//		Barrier , Fence
	//									��3���߼�������������
};

enum class RFGPassType
{
	Depth,
	Gbuffer,
	Lighting,
	Shdow,
	Material,
	Post,

	Debug,
};

enum class RFGPTaskQueueType
{
	Graphics,
	Compute,
	Copy,
	//		Barrier , Fence
	//									��3���߼�������������
};





struct RFGResourceInfo
{
	//RFGResourceInfo(resource::Buffer::ResourceInfo RI) :ResourceInfo(RI) {};

	friend class RenderFrameGraph;
	friend class VitualResourceManager;

	//std::string			name;
	//resource::Buffer::ResourceInfo		ResourceInfo;
	//uint32_t			ID;
private:
	uint32_t			Lifes;
	//std::vector<std::string>			Read;
	/*std::vector<std::string>			Write;*/
	std::vector<uint32_t>			Read;
	std::vector<uint32_t>			Write;
	
};

//				�ػ��� Graphics �� Compute �ֱ��PassInfo & Resource Info?	Ȼ������ʽ����ϸ��?
struct RFGPassInfo
{
	std::string							name;
	renderpass::Pass_Mat_Info*			PassDataInfo;

	RFGPassQueueType					QueueType;
	RFGPassType							PassType;
	std::vector<std::string>			In;
	std::vector<std::string>			Out;

};

struct RFGTaskInfo
{
	RFGPTaskQueueType  QueueType;
};


class RenderFrameGraph
{
public:
	RenderFrameGraph() {};
	~RenderFrameGraph() {};

	
	//	�����ֶ��Ӱ�,�����Ϳ��Լ�һ�� if �߼���
	void Add_Pass(RFGPassInfo PI) 
	{ 
		RFG_PassInfos.push_back(PI);	
		//PassInfoNum++;
		//RFG_PassInfoID.emplace(PI.name, PassInfoNum++);
	}
	void Add_Resource(std::string name )
	{
		//	�������ظ������ֵ,�Ҳ��Ḳ��
		//	���������Ļ�ÿ����Դ��Buffer::resourceInfoֻ��һ��
		//	Ҳ���Ǿ���״̬�ñ�����PassInfo��
		//	���߱����Resource��<Pass , State>����
		RFG_ResourceInfoID.emplace(name, ResourceInfoNum++);
		RFG_ResourceInfos.push_back(RFGResourceInfo());
	}
	void Add_Global_Resource(std::string name)
	{

	};
	//void Add_Read_Resource(RFGResourceInfo R)		
	//{	
	//	RFG_Read_Resources .push_back( R )	;	
	//	//RFG_ResourceInfoID.emplace(R.name,ResourceNum++);	
	//};
	//void Add_Write_Resource(RFGResourceInfo R) 
	//{ 
	//	RFG_Write_Resources.push_back(R);	
	//	//RFG_ResourceInfoID.emplace(R.name, ResourceNum++);
	//};

	//
	void setup();
	//	��������,�������
	void compiler();
	//	����Task
	void excute();

	

private:
	std::unordered_map<std::string, uint32_t>			RFG_Graphics_Pass_InfoID;
	std::unordered_map<std::string, uint32_t>			RFG_Compute_Pass_InfoID;
	std::unordered_map<std::string, uint32_t>			RFG_ResourceInfoID;
	//std::unordered_map<std::string, uint32_t>			RFG_Read_ResourceID;
	//std::unordered_map<std::string, uint32_t>			RFG_Write_ResourcID;

	uint32_t				PassInfoNum=0;
	uint32_t				ResourceInfoNum=0;
	//uint32_t				ResourceNum;		��д�ֱ��0��ʼ��ID , ���ǹ���һ��?

	std::vector	<RFGPassInfo>								RFG_PassInfos;
	std::vector	<RFGResourceInfo>							RFG_ResourceInfos;
	//std::vector	<RFGPassInfo>							RFG_Graphics_PassInfos;
	//std::vector	<RFGPassInfo>							RFG_Compute_PassInfos;
	//std::vector	<RFGResourceInfo>						RFG_Read_Resources;
	//std::vector	<RFGResourceInfo>						RFG_Write_Resources;
	//std::unordered_map<std::string, RFGResourceInfo>		RFG_ResourceInfos;
	//std::unordered_map<std::string, RFGResourceInfo>		RFG_Read_Resources;
	//std::unordered_map<std::string, RFGResourceInfo>	    RFG_Write_Resources;

	//		��������Node ID ӳ�䵽	Name��?
	VirtualResourceManager									VRM;
};


class VirtualResourceManager
{
	//			Node	��Resource ���ӵı���Pass  ,Ȼ��������Pass����VNode
	//			VNode	��Resource ���ӵ�Ҳ��Pass  ,ͬ��
	enum class NodeType
	{
		Resource,

		Pass,

		Barrier,
		Fence
	};

	struct NodeIndex
	{
	public:
		NodeIndex() {};
		NodeIndex(bool a, uint32_t b) :IsVNode(a), Index(b) {};
		bool IsVNode;
		uint32_t Index;
	};


	struct Node
	{
	public:
		
		NodeType	Type;

		uint32_t	Read=-1;
		uint32_t	Write=-1;

		bool        IsUsed=1;
		uint32_t	VNode_Index;
	};


	struct VNode
	{
	public:
		NodeType				Type;

		std::vector<NodeIndex>	Reads;
		std::vector<NodeIndex>	Writes;
	};


public:

	std::vector<Node>		Nodes;
	std::vector<VNode>		VNodes;

	std::unordered_map<std::string, NodeIndex>	Name_Index;

	uint32_t				NodeNum=0;
	uint32_t				VNodeNum = 0;

	//			1����û����Դû��дֱ�Ӷ� , ��������Pass���ǿ�ʼ
	//			0�����ж���д  ,  �϶����м䲽����
	std::bitset<1024>		Node_Heads;
	std::bitset<1024>		VNode_Heads;

	void		Add_Node(RFGPassInfo& PassInfo);

public:
	VirtualResourceManager() {};
	~VirtualResourceManager() {};

	 
};



}