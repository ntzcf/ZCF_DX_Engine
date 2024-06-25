#include "Render/Renderer.h"
#include "Render/SrcRenderHelper.h"
#include "Render/RenderPass.h"
#include "Render/RenderResourceManager.h"
#include "Render/Buffer.h"
using namespace resource::Buffer;

namespace Engine::Render::renderer
{
	void Renderer::Init()
	{
	}
	void Renderer::Update()
	{
	}
	void Renderer::run()
	{
		RenderBegin();
		Render();
		RenderEnd();
	}
	void Renderer::Render()
	{
		LearnPass();
	}
	void Renderer::RenderBegin()
	{
		//��ִ֡��ͼ����clearΪ��֡�ռ�ͼ
		//RFG = RFGs[frameCount % 2].get.reset();
	}
	void Renderer::RenderEnd()
	{
		//Fence:�ȱ�ִ֡��ͼ
		// �����߳���ͼ
		//����:��֡���ռ�ͼ��ʼ����;
		// ��дһ��lamada,�����Լ���,����End����Χ�� ע:�ռ�ͼ��Ϊ��					���ñ���ִ���߳�
		//Present:�ϴ�������
	}
	void Renderer::LearnPass()
	{
		renderpass::LearnPassInfo LPI;
		LPI.PassCollectBegin();
		LPI.PassCollect();//	���︺��Ѽ���Ĺ̶�����������?
		LPI.Lamda=[&](Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CL, resource::RenderResourceManager RRM,
			Microsoft::WRL::ComPtr<ID3D12Device> Device)->void
		{
			auto FGR = RRM.GetFrameGraphicsResource("LearnPass");

///////////////////////////////////////////////////////////////    PSO
			CL->SetPipelineState(FGR->PSO.Get());
			
////////////////////////////////////////////////////////////////	Vertex_Index_buffers
			std::vector<D3D12_VERTEX_BUFFER_VIEW>  VBVs;
			std::vector<D3D12_INDEX_BUFFER_VIEW>   IBVs;

			for (auto VIB : FGR->V_I_Buffers)
			{
				if (VIB->GetAttribute() == VertexAttribute::Index)
				{
					D3D12_INDEX_BUFFER_VIEW IBV;
					IBV.BufferLocation	=	VIB->Resource.Get()->GetGPUVirtualAddress();
					IBV.SizeInBytes		=	VIB->Size / 8;
					IBV.Format			=	VIB->Nums > 65536?  DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
					IBVs.push_back(std::move(IBV));
				}
				else
				{
					D3D12_VERTEX_BUFFER_VIEW VBV;
					VBV.BufferLocation = VIB->Resource.Get()->GetGPUVirtualAddress();
					VBV.SizeInBytes = VIB->Size / 8;
					VBV.StrideInBytes = VIB->OneBits/8;
					VBVs.push_back(std::move(VBV));
				}
			}
			//           ��������Slot  ����PSO��InputLayput����һ�����а� , ����ѭ�������øĽ�.
			//           ���Ը���ѭ��, ����̶�Position�߿�ʼslotS ,  Normal��slotS+1 ,   UV0�ߺ�slotS+2
			//           ����һ����ʼslot,  �ٶ�����slot����������
			//			 �Ѱ󶨸��Ƶ�ѭ����.
			CL->IASetVertexBuffers(0,VBVs.size(),VBVs.data());
			CL->IASetIndexBuffer(IBVs.data());
			//			IndexBuffer����̶�ֻ��һ��,û��Ҫvector��
/////////////////////////////////////////////////////////	Topology


////////////////////////////////////////////////////////	ViewPort


///////////////////////////////////////////////////////		Scissor

//////////////////////////////////////////////////////		RTV
			//				num
			auto RTVnums = FGR->RenderTargets.size();
			std::vector<CD3DX12_CPU_DESCRIPTOR_HANDLE>	RTVs(RTVnums);
			//				handle
			auto handle = ( FGR->RTV_Heap->GetCPUDescriptorHandleForHeapStart());
			//				handle_Start
			auto RTV_size = FGR->RTV_DescriptorSize;
			INT64 RTV_start_Offset = FGR->RTV_StartIndex * RTV_size;
			handle.ptr = SIZE_T(INT64(handle.ptr) + RTV_start_Offset);
			//				RTV_names
			std::vector<std::string > RTV_names(RTVnums);
			RTV_names.push_back( "RenderTarget" );
			//				Handles
			std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> Handles(RTVnums);
			//				loop
			for (int i = 0; i < RTVnums; i++)
			{
				Device->CreateRenderTargetView(FGR->RenderTargets[RTV_names[i]]->Resources.Get(), nullptr, handle);
				Handles.push_back(handle);
				handle.ptr = SIZE_T(INT64(handle.ptr) +RTV_size );
			}
			//				Set
			CL->OMSetRenderTargets(RTVnums, Handles.data(), 1, FGR->DSV);
			

				//CL.BeginPass();
				//CL.SetRenderTargets(RTVs.num(),RTV_Handles.data(),RTVs.Single,FR.DSV);
				//CL.ClearRT(...);
				// 
				// 
				// 
				//auto SRV_Heap=FR.GetSRT_Heap()
				// auto SRs = FR.GetSR(R1name)
				//   for ( R ; SRs )  Device->CreateSRV(SRV_H , R.GPUVirtualAddress) 
				//
				// auto CBV_H = FR.GetCBV_H
				//auto CRs = FR.GetCR("R2name");
				//  for(R:CRs)   Device -> CreateCBV(CBV_H , R.GVA)
				//CL.SetDesciptorHeap(SRV_H   ,  CBV_H );
				//CL.SetDescriptorParemeters( SRV_H.Start ,   CBV_H.Start );
				////UAV����
				//CL.DrawType();
				//CL.EndPass();
		};
		
		LPI.PassCollectEnd();


		//RFG Pass & Resource Info	-->	RFG	-->	RRM

		//RRM.CreatePassResource(&PassInfo)
		RRM->CreateLearnPassResource(std::move(LPI));
	}
}