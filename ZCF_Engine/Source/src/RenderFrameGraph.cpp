#include "Render/RenderFrameGraph.h"
#include "Render/SrcRenderHelper.h"


namespace Engine::Render::frameGraph
{
	void RenderFrameGraph::setup()
	{
		/*for (int i; i < PassInfoNum; i++)
		{
			if (RFG_PassInfos[i].QueueType == RFGPassQueueType::Graphics)
			{
				RFG_Graphics_Pass_InfoID.emplace(RFG_PassInfos[i].name, i);
				
				int num = RFG_PassInfos[i].In.size();
				for (size_t i = 0; i < num; i++)
				{
					RFG_Resources[RFG]
				}
			}

			if (RFG_PassInfos[i].QueueType == RFGPassQueueType::Compute)
			{
				RFG_Compute_Pass_InfoID.emplace(RFG_PassInfos[i].name, i);
			}
		}*/
		for (auto Pass : RFG_PassInfos)
		{
			if (Pass.QueueType == RFGPassQueueType::Graphics)
			{
				RFG_Graphics_Pass_InfoID.emplace(Pass.name, PassInfoNum);

				for (auto name: Pass.In)
				{
					//		
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Lifes++;
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Write.push_back( PassInfoNum);
				}
				for (auto name : Pass.Out)
				{
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Lifes++;
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Read.push_back(PassInfoNum);
				}
			}

			if (Pass.QueueType == RFGPassQueueType::Compute)
			{
				RFG_Compute_Pass_InfoID.emplace(Pass.name, PassInfoNum);

				for (auto name : Pass.In)
				{
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Lifes++;
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Write.push_back(PassInfoNum);
				}
				for (auto name : Pass.Out)
				{
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Lifes++;
					RFG_ResourceInfos[RFG_ResourceInfoID[name]].Read.push_back(PassInfoNum);
				}
			}

			PassInfoNum++;
		}
		//	当for循环结束时,所有会被用到的Pass与资源关系都已被确认.
		//	并且资源的具体使用数据在每个Pass的DataInfo中
		//	
	}
	void RenderFrameGraph::compiler()
	{
		//	Graphics , Ccompute 分别的串行序列:资源依赖,屏障,合批......	  队列间同步:
		//	别名重用:
		//	Pass合并 :(Vulkan的Pass与sub Pass)	或者	(直接合并成一个Pass)
		for (auto Pass : RFG_PassInfos)
		{

		}
		
	}
	void VirtualResourceManager::Add_Node(RFGPassInfo& PassInfo)
	{
		//if (PassInfo.In.size() > 1 || PassInfo.Out.size() > 1)
		{
			VNode P1Node;
			P1Node.Type = NodeType::Pass;
			auto PassIndex = VNodeNum;

			VNodes.push_back(std::move(P1Node));
			Name_Index.emplace(PassInfo.name, VNodeNum++);

			VNode* PNode = &VNodes[PassIndex];



			for (auto R : PassInfo.In)
			{
				auto find = Name_Index.find(R);
				if(find==Name_Index.end())
				{
					PNode->Reads.emplace_back(0,NodeNum);

					Node Rnode;
					Rnode.Type = NodeType::Resource;
					Rnode.Read = PassIndex;
					Rnode.Write = -1;
					Nodes.push_back(std::move(Rnode));

					Node_Heads.set(NodeNum);

					Name_Index.emplace(R, NodeNum++);
				}
				if(find!=Name_Index.end() && Nodes[find->second.Index].Read==-1)
				{
					PNode->Reads.emplace_back(0, find->second.Index);
					Nodes[find->second.Index].Read = PassIndex;
				}

				else
				{	
						bool isV = Name_Index[R].IsVNode;
						

						if(isV)
						{
							uint32_t Vindex = Name_Index[R].Index;

							PNode->Reads.emplace_back(1, Vindex);

							VNodes[Vindex].Reads.emplace_back(1,PassIndex);

						}

						if(!isV)
						{
							uint32_t index = Name_Index[R].Index;

							Nodes[index].IsUsed = 0;

							uint32_t read = Nodes[index].Read;
							uint32_t write = Nodes[index].Write;

							if (read > 0)
								VNodes[read].Reads.emplace_back(1, VNodeNum);
							if (write > 0)
								VNodes[write].Writes.emplace_back(1, VNodeNum);
							if(write==-1)
								VNode_Heads.set(VNodeNum);

							VNode Res;
							Res.Type = NodeType::Resource;
							Res.Writes.emplace_back(1, write);
							Res.Reads.emplace_back(1, read);
							Res.Reads.emplace_back(1, PassIndex);

							PNode->Reads.emplace_back(1, VNodeNum);

							VNodes.push_back(std::move(Res));

							Name_Index[R].IsVNode = 1;
							Name_Index[R].Index = VNodeNum++;
						}

				}
			}
			for (auto R : PassInfo.Out)
			{
				auto find = Name_Index.find(R);
				if (find==Name_Index.end())
				{
					PNode->Writes.emplace_back(0,NodeNum);

					Node node;
					node.Type = NodeType::Resource;
					node.Write = PassIndex;
					node.Read = -1;
					Nodes.push_back(std::move(node));

					Name_Index.emplace(R, NodeNum++);
				}
				if (find != Name_Index.end() && Nodes[find->second.Index].Write == -1)
				{
					PNode->Writes.emplace_back(0, find->second.Index);
					Nodes[find->second.Index].Write = PassIndex;

					Node_Heads.reset(find->second.Index);
				}
				else
				{
					bool isV = Name_Index[R].IsVNode;
					

					if (isV)
					{	
						uint32_t Vindex = Name_Index[R].Index;

						PNode->Writes.emplace_back(1, Vindex);

						VNodes[Vindex].Writes.emplace_back(1, PassIndex);
						
						VNode_Heads.reset(Vindex);
						

					}

					if (!isV)
					{

						uint32_t index = Name_Index[R].Index;

						Nodes[index].IsUsed = 0;

						uint32_t read = Nodes[index].Read;
						uint32_t write = Nodes[index].Write;

						if (read > 0)
							VNodes[read].Reads.emplace_back(1, VNodeNum);
						if (write > 0)
							VNodes[write].Writes.emplace_back(1, VNodeNum);

						VNode Res;
						Res.Type = NodeType::Resource;
						Res.Writes.emplace_back(1, write);
						Res.Writes.emplace_back(1, PassIndex);
						Res.Reads.emplace_back(1, read);

						PNode->Writes.emplace_back(1, VNodeNum);

						VNodes.push_back(std::move(Res));

						Name_Index[R].IsVNode = 1;
						Name_Index[R].Index = VNodeNum++;
					}

				}
			}
			
		}
	}

};