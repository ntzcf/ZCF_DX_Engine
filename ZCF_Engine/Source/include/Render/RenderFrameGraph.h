#pragma once
#include "d3dUtil.h"
#include "Buffer.h"
#include "RenderPass.h"

#include <bitset>

/// <summary>
/// /////////////////////////////////核心:	读	和	写	///////////////////////////////////////////////////////////////
/// </summary>
namespace Engine::Render::frameGraph
{
	struct RFGPassInfo;

//						8维条件
// 	   [Pass , Passes]	(PassInfo , ResourceInfo , QueueInfo , ResourceState(Barrier))
// 
enum class RFGPassQueueType
{
	Graphics,
	Compute,
	//Copy,
	//		Barrier , Fence
	//									建3种逻辑队列来放命令
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
	//									建3种逻辑队列来放命令
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

//				特化出 Graphics 与 Compute 分别的PassInfo & Resource Info?	然后套娃式继续细分?
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

	
	//	还是手动加吧,这样就可以加一层 if 逻辑层
	void Add_Pass(RFGPassInfo PI) 
	{ 
		RFG_PassInfos.push_back(PI);	
		//PassInfoNum++;
		//RFG_PassInfoID.emplace(PI.name, PassInfoNum++);
	}
	void Add_Resource(std::string name )
	{
		//	不允许重复加入键值,且不会覆盖
		//	但是这样的话每个资源的Buffer::resourceInfo只有一份
		//	也就是具体状态得保存在PassInfo中
		//	或者保存个Resource的<Pass , State>集合
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
	//	连接依赖,添加屏障
	void compiler();
	//	生成Task
	void excute();

	

private:
	std::unordered_map<std::string, uint32_t>			RFG_Graphics_Pass_InfoID;
	std::unordered_map<std::string, uint32_t>			RFG_Compute_Pass_InfoID;
	std::unordered_map<std::string, uint32_t>			RFG_ResourceInfoID;
	//std::unordered_map<std::string, uint32_t>			RFG_Read_ResourceID;
	//std::unordered_map<std::string, uint32_t>			RFG_Write_ResourcID;

	uint32_t				PassInfoNum=0;
	uint32_t				ResourceInfoNum=0;
	//uint32_t				ResourceNum;		读写分别从0开始的ID , 还是共用一套?

	std::vector	<RFGPassInfo>								RFG_PassInfos;
	std::vector	<RFGResourceInfo>							RFG_ResourceInfos;
	//std::vector	<RFGPassInfo>							RFG_Graphics_PassInfos;
	//std::vector	<RFGPassInfo>							RFG_Compute_PassInfos;
	//std::vector	<RFGResourceInfo>						RFG_Read_Resources;
	//std::vector	<RFGResourceInfo>						RFG_Write_Resources;
	//std::unordered_map<std::string, RFGResourceInfo>		RFG_ResourceInfos;
	//std::unordered_map<std::string, RFGResourceInfo>		RFG_Read_Resources;
	//std::unordered_map<std::string, RFGResourceInfo>	    RFG_Write_Resources;

	//		考虑来个Node ID 映射到	Name的?
	VirtualResourceManager									VRM;
};


class VirtualResourceManager
{
	//			Node	的Resource 连接的必是Pass  ,然后让所有Pass属于VNode
	//			VNode	的Resource 连接的也是Pass  ,同理
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

	//			1就是没有资源没有写直接读 , 他相连的Pass就是开始
	//			0就是有读有写  ,  肯定是中间步骤了
	std::bitset<1024>		Node_Heads;
	std::bitset<1024>		VNode_Heads;

	void		Add_Node(RFGPassInfo& PassInfo);

public:
	VirtualResourceManager() {};
	~VirtualResourceManager() {};

	 
};



}