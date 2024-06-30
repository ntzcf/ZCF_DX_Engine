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
		//	��forѭ������ʱ,���лᱻ�õ���Pass����Դ��ϵ���ѱ�ȷ��.
		//	������Դ�ľ���ʹ��������ÿ��Pass��DataInfo��
		//	
	}
	void RenderFrameGraph::compiler()
	{
		//	Graphics , Ccompute �ֱ�Ĵ�������:��Դ����,����,����......	  ���м�ͬ��:
		//	��������:
		//	Pass�ϲ� :(Vulkan��Pass��sub Pass)	����	(ֱ�Ӻϲ���һ��Pass)
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
				if(Name_Index.find(R)==Name_Index.end())
				{
					PNode->Reads.emplace_back(0,NodeNum);

					Node Rnode;
					Rnode.Type = NodeType::Resource;
					Rnode.Read = PassIndex;
					Rnode.Write = -1;
					Nodes.push_back(std::move(Rnode));

					Name_Index.emplace(R, NodeNum++);
				}

				else
				{	
						bool isV = Name_Index[R].IsVNode;
						uint32_t index = Name_Index[R].Index;

						if(isV)
						{
							PNode->Reads.emplace_back(1, index);

							VNodes[index].Reads.emplace_back(1,PassIndex);

						}

						if(!isV)
						{
							

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
				if (Name_Index.find(R) == Name_Index.end())
				{
					PNode->Writes.emplace_back(0,NodeNum);

					Node node;
					node.Type = NodeType::Resource;
					node.Write = PassIndex;
					node.Read = -1;
					Nodes.push_back(std::move(node));

					Name_Index.emplace(R, NodeNum++);
				}
				else
				{
					bool isV = Name_Index[R].IsVNode;
					uint32_t index = Name_Index[R].Index;

					if (isV)
					{
						PNode->Writes.emplace_back(1, index);

						VNodes[index].Writes.emplace_back(1, PassIndex);

					}

					if (!isV)
					{

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