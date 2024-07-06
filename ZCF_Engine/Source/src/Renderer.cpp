#include "Render/Renderer.h"
#include "Render/RenderPassInfo.h"
#include "Render/RenderManager.h"
#include "Render/ResAttribute.h"
#include "Render/RenderFrameGraph.h"

using namespace  Engine::Render::renderpass;
using namespace  Engine::Render::resource;

namespace Engine::Render
{
	void Renderer::Init(  scene::SceneManager	*SM)
	{
		SceneManager = SM;
	}
	void Renderer::Update()
	{
		//RFG = std::make_unique<RenderFrameGraph>(new RenderFrameGraph);
	}
	void Renderer::run()
	{
		RenderBegin();
		Render();
		RenderEnd();
	}
	void Renderer::Render()
	{
		//LearnPass();
		DepthPass();
	}
	void Renderer::RenderBegin()
	{
		//��ִ֡��ͼ����clearΪ��֡�ռ�ͼ
		//RFG = RFGs[frameCount % 2].get.reset();
	}
	void Renderer::RenderEnd()
	{
		//RFG->setup();
		//RFG->compiler();
		//RFG->excute();
		//Fence:�ȱ�ִ֡��ͼ
		// �����߳���ͼ
		//����:��֡���ռ�ͼ��ʼ����;
		// ��дһ��lamada,�����Լ���,����End����Χ�� ע:�ռ�ͼ��Ϊ��					���ñ���ִ���߳�
		//Present:�ϴ�������
	}
	void Renderer::DepthPass()
	{
		DepthPassInfo PassInfo;
		
		PassInfo.ResourceInfos.emplace(ResourceUsage::DSV, ("DepthBuffer", ResourceFormat::Format_D24_UNORM_S8_UINT));
		
		PassInfo.isGraphics = 1;
		
		PassInfo.PassName = "DepthPass";
		//Vertex
		//Index

		//PassInfo.Vertex_Attribute_Stream.emplace
		//(SceneManager->GetVAS()->at(scene::Object::Vertex_Attribute::Position));
		//PassInfo.Index_Stream.emplace(SceneManager->GetIS()->data());

		//PassInfo.RenderPSO.Shader		��Ҳ��װ��һ��������?
		PassInfo.RenderPSO.InputViews.emplace_back("position", 0, ResourceFormat::RGBA_32_FLOAT, 0, 12, 0, 0);
		//PassInfo.RenderPSO.BlendState.push_back(BlendState::DefaultBlend);
		//PassInfo.RenderPSO.MutiSample;
		//PassInfo.RenderPSO.Rasterize.CullMode = CullMode::Back;
		//PassInfo.RenderPSO.Rasterize.FillMode = FillMode::Solid;
		//PassInfo.RenderPSO.Rasterize.FrontCounterClockwise = 0;
		PassInfo.RenderPSO.RenderTargetNum = 0;
		//PassInfo.RenderPSO.Topolopy = Topology::Triangle;
		PassInfo.RenderPSO.Shaders.emplace_back(ShaderType::VS, "DepthPass", "VS",
			"E:/My projects/DX12_Engine/ZCF_Engine/ZCF_Engine/Source/shaders",
			"vs_5_0", "0", "0");
		PassInfo.RenderPSO.Shaders.emplace_back(ShaderType::PS, "DepthPass", "PS",
			"E:/My projects/DX12_Engine/ZCF_Engine/ZCF_Engine/Source/shaders",
			"Ps_5_0", "0", "0");
		PassInfo.Lamda=[](ID3D12GraphicsCommandList *cmdlist , const FrameGraphicsPassResource &Resource)
		{
			cmdlist->SetPipelineState(Resource.PSO.Get());
				   
			cmdlist->IASetVertexBuffers(0,Resource.VBV.size(), Resource.VBV.data());
			cmdlist->IASetIndexBuffer(Resource.IBV);
				   
			//cmdli->t.Get()->SetDescriptorHeaps(0,Resource.Heaps.data());
			//cmdli->t->SetGraphicsRoot32BitConstants(0u, 3u, reinterpret_cast<void*>(Resource.Constants.data()), 0u);
				   
			cmdlist->OMSetRenderTargets(Resource.RTVs.size(), Resource.RTVs.data(), 1, Resource.DSV);
			//		>-	���������Ĳ��־��ֶ����� , �ܲ�����ȫ�Զ���
			cmdlist->RSSetViewports();
			cmdlist->RSSetScissorRects();
				   
			cmdlist->DrawIndexedInstanced();
		};
		//RFG->Add_Pass();
		//RFG->Add_Resource();

		
	}
	void Renderer::GBufferPass()
	{
		GBufferPassInfo PassInfo;

		PassInfo.Resources.emplace(ResourceUsage::RTV, ("GBuffer0", ResourceFormat::RGBA_32_FLOAT));
		PassInfo.Resources.emplace(ResourceUsage::RTV, ("GBuffer1", ResourceFormat::RGBA_32_FLOAT));
		PassInfo.Resources.emplace(ResourceUsage::RTV, ("GBuffer2", ResourceFormat::RGBA_32_FLOAT));
		PassInfo.Resources.emplace(ResourceUsage::RTV, ("GBuffer3", ResourceFormat::RGBA_32_FLOAT));
		PassInfo.Resources.emplace(ResourceUsage::DSV, ("DepthBuffer", ResourceFormat::Format_D24_UNORM_S8_UINT));

		PassInfo.isGraphics = 1;

		PassInfo.PassName = "DepthPass";
		//Vertex
		//Index

		PassInfo.RenderPSO.InputViews.emplace_back("position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, 0, 0);
		PassInfo.RenderPSO.InputViews.emplace_back("normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 12, 0, 0);
		PassInfo.RenderPSO.InputViews.emplace_back("tangent", 0, DXGI_FORMAT_R32G32B32_FLOAT, 2, 12, 0, 0);
		PassInfo.RenderPSO.InputViews.emplace_back("basecolor", 0, DXGI_FORMAT_R32G32B32_FLOAT, 3, 12, 0, 0);
		//PassInfo.RenderPSO.BlendState.push_back(BlendState::DefaultBlend);
		//PassInfo.RenderPSO.MutiSample;
		//PassInfo.RenderPSO.Rasterize.CullMode = CullMode::Back;
		//PassInfo.RenderPSO.Rasterize.FillMode = FillMode::Solid;
		//PassInfo.RenderPSO.Rasterize.FrontCounterClockwise = 0;
		PassInfo.RenderPSO.RenderTargetNum = 4;
		//PassInfo.RenderPSO.Topolopy = Topology::Triangle;
		PassInfo.RenderPSO.Shaders.emplace_back(ShaderType::VS, "GBufferPass", "VS",
			"E:/My projects/DX12_Engine/ZCF_Engine/ZCF_Engine/Source/shaders",
			"vs_5_0", "0", "0");
		PassInfo.RenderPSO.Shaders.emplace_back(ShaderType::PS, "GBufferPass", "PS",
			"E:/My projects/DX12_Engine/ZCF_Engine/ZCF_Engine/Source/shaders",
			"Ps_5_0", "0", "0");

		PassInfo.Lamda = [](ID3D12GraphicsCommandList* cmdlist, const FrameGraphicsPassResource& Resource)
		{
			cmdlist->SetPipelineState(Resource.PSO.Get());

			cmdlist->IASetVertexBuffers(0, Resource.VBV.size(), Resource.VBV.data());
			cmdlist->IASetIndexBuffer(Resource.IBV);

			//cmdli->t.Get()->SetDescriptorHeaps(0,Resource.Heaps.data());
			//cmdli->t->SetGraphicsRoot32BitConstants(0u, 3u, reinterpret_cast<void*>(Resource.Constants.data()), 0u);

			cmdlist->OMSetRenderTargets(Resource.RTVs.size(), Resource.RTVs.data(), 4, Resource.DSV);
			//		>-	���������Ĳ��־��ֶ����� , �ܲ�����ȫ�Զ���
			cmdlist->RSSetViewports();
			cmdlist->RSSetScissorRects();

			cmdlist->DrawIndexedInstanced();
		};

		/*int num = SceneManager->GetVAS()->size();
		for (int i = 0; i < num; i++)
		{
			PassInfo.Vertex_Attribute_Stream.emplace
			(SceneManager->GetVAS()->at(Object::Vertex_Attribute::Position));
		}
		PassInfo.Index_Stream.emplace(SceneManager->GetIS()->data());*/



	}
	//	void Renderer::LearnPass()
//	{
//		renderpass::LearnPassInfo LPI;
//		LPI.PassCollectBegin();
//		LPI.PassCollect();//	���︺��Ѽ���Ĺ̶�����������?
//		LPI.Lamda=[&](Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CL, resource::RenderResourceManager RRM,
//			Microsoft::WRL::ComPtr<ID3D12Device> Device)->void
//		{
//			auto FGR = RRM.GetFrameGraphicsResource("LearnPass");
//
/////////////////////////////////////////////////////////////////    PSO
//			CL->SetPipelineState(FGR->PSO.Get());
//			
//////////////////////////////////////////////////////////////////	Vertex_Index_buffers
//			std::vector<D3D12_VERTEX_BUFFER_VIEW>  VBVs;
//			std::vector<D3D12_INDEX_BUFFER_VIEW>   IBVs;
//
//			for (auto VIB : FGR->V_I_Buffers)
//			{
//				if (VIB->GetAttribute() == VertexAttribute::Index)
//				{
//					D3D12_INDEX_BUFFER_VIEW IBV;
//					IBV.BufferLocation	=	VIB->Resource.Get()->GetGPUVirtualAddress();
//					IBV.SizeInBytes		=	VIB->Size / 8;
//					IBV.Format			=	VIB->Nums > 65536?  DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
//					IBVs.push_back(std::move(IBV));
//				}
//				else
//				{
//					D3D12_VERTEX_BUFFER_VIEW VBV;
//					VBV.BufferLocation = VIB->Resource.Get()->GetGPUVirtualAddress();
//					VBV.SizeInBytes = VIB->Size / 8;
//					VBV.StrideInBytes = VIB->OneBits/8;
//					VBVs.push_back(std::move(VBV));
//				}
//			}
//			//           ��������Slot  ����PSO��InputLayput����һ�����а� , ����ѭ�������øĽ�.
//			//           ���Ը���ѭ��, ����̶�Position�߿�ʼslotS ,  Normal��slotS+1 ,   UV0�ߺ�slotS+2
//			//           ����һ����ʼslot,  �ٶ�����slot����������
//			//			 �Ѱ󶨸��Ƶ�ѭ����.
//			CL->IASetVertexBuffers(0,VBVs.size(),VBVs.data());
//			CL->IASetIndexBuffer(IBVs.data());
//			//			IndexBuffer����̶�ֻ��һ��,û��Ҫvector��
///////////////////////////////////////////////////////////	Topology
//
//
//////////////////////////////////////////////////////////	ViewPort
//
//
/////////////////////////////////////////////////////////		Scissor
//
////////////////////////////////////////////////////////		RTV
//			//				num 
//			auto RTVnums = FGR->RenderTargets.size();
//			//				handle
//			auto handle = ( FGR->RTV_Heap->GetCPUDescriptorHandleForHeapStart());
//			//				handle_Start
//			auto RTV_size = FGR->RTV_DescriptorSize;
//			INT64 RTV_start_Offset = FGR->RTV_StartIndex * RTV_size;
//			handle.ptr = SIZE_T(INT64(handle.ptr) + RTV_start_Offset);
//			//				RTVs
//			std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>	RTVs(RTVnums);
//			//				RTV_names
//			std::vector<std::string > RTV_names(RTVnums);
//			RTV_names.push_back( "RenderTarget" );
//			//				loop
//			for (int i = 0; i < RTVnums; i++)
//			{
//				Device->CreateRenderTargetView(FGR->RenderTargets[RTV_names[i]]->Resources.Get(), nullptr, handle);
//				RTVs.push_back(handle);
//				CL->ClearRenderTargetView(handle, 0, 0, nullptr);
//				handle.ptr = SIZE_T(INT64(handle.ptr) +RTV_size );
//			}
//			//             DSV
//			CL->ClearDepthStencilView(*(FGR->DSV), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
//
//			//			Set
//			CL->OMSetRenderTargets(RTVnums, RTVs.data(), 1, FGR->DSV);
//			
//////////////////////////////////////////////////	CBV  SRV	Constant----------------Bindless Texture
////			
//				//CL.BeginPass();
//				//CL.SetDesciptorHeap(SRV_H   ,  CBV_H );
//				//CL.SetDescriptorParemeters( SRV_H.Start ,   CBV_H.Start );
//				////UAV����
//				//CL.DrawType();
//				//CL.EndPass();
//		};	
//		LPI.PassCollectEnd();
//
//////////////////////////////////////////////////////////////////RFG
//
//		frameGraph::RenderFrameGraph RFG;
//
//		frameGraph::RFGPassInfo			Pass;
//		Pass.name = "LearnPass";
//		Pass.QueueType = frameGraph::RFGPassQueueType::Graphics;
//		
//		int size = LPI.InResourceInfos.size();
//		for (int i = 0; i < size; i++)
//		{
//			frameGraph::RFGResourceInfo RI;
//			RI.name = LPI.InResourceInfos[i].name;
//			RFG.Add_Read_Resource(RI);
//			Pass.Reads.push_back(std::move(RI));
//		}
//
//		size = LPI.OutResourceInfos.size();
//		for (int i = 0; i < size; i++)
//		{
//			frameGraph::RFGResourceInfo RI;
//			RI.name = LPI.OutResourceInfos[i].name;
//			RFG.Add_Write_Resource(RI);
//			Pass.Writes.push_back(std::move(RI));
//		}
//
//		RFG.Add_Pass(std::move(Pass));
//
//		//		��Ҫ������Դ,��Pass�ľ����ڲ���Ϣ,	�ü�ʱ����ѡ���ٷ���һЩ����.
//		//		���鷳������
//
//		//		RFG������(Ԥ��������,ͬ������),����,ִ��
//		//		ͳһִ��, �ֲ�����ִ��
//		//		ȫ�ֶ���ע��............
//	}
}