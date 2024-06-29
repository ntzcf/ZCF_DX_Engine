#pragma once
#include "RenderFrameGraph.h"
#include "d3dUtil.h"
#include "RenderPass.h"
#include "Scene/SceneManager.h"

class RenderResourceManager;

namespace Engine::Render::renderer
{
class Renderer
{
public:
	Renderer() {};
	~Renderer() {};

	void Init();
	void Update();
	void run();

	//resource::RenderResourceManager* RRM;

private:
	void Render();
	//֡��ͬ��
	void RenderBegin();
	void RenderEnd();
	
	//����
	//void LearnPass();

	void PassBegin();
	void PassEnd();

	//Gpu Driven PipeLine
	//���޳�:cpu+gpu
	void CullPass();
	void HizPass();
	//���ͼ
	void DepthPass();
	//Visible-G-Buffer
	void VisibleGPass();
	//ShdowMap
	void ShdowPass();
	//Lighting
	void LightingPass();
	//Material
	void ShadingPass();
	//�����ͼû������ȥ����hiz-buffer:���Գ��Ź���,������Щʱ��ȥ����
	void GeneraHizPass();
	//Post
	void PostPasses();

	//Debug
	void DebugPasses();
	


private:

	std::shared_ptr<frameGraph::RenderFrameGraph>		RFGs[2];
	
	std::vector<renderpass::DepthPassInfo>					DepthPasses;
	std::vector<renderpass::GBufferPassInfo>				GBufferPasses;
	std::vector<renderpass::LightingPassInfo>				LightingPasses;
	std::vector<renderpass::MaterialPassInfo>				MaterialPasses;

	//						ͳһ�ռ�Texture , ConstantBuffer , RootConstant Ȼ�󽻸�RRM�ϴ�
	// 
	// 
	// 



		// ������������С���붼�� 256 �ֽڵ���������
		//static const UINT c_alignedConstantBufferSize = (sizeof(ModelViewProjectionConstantBuffer) + 255) & ~255;


		//���弸�ε� Direct3D ��Դ��
		//Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>		m_commandList;
		//Microsoft::WRL::ComPtr<ID3D12RootSignature>			m_rootSignature;
		//Microsoft::WRL::ComPtr<ID3D12PipelineState>			m_pipelineState;
		//Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>			m_cbvHeap;
		//Microsoft::WRL::ComPtr<ID3D12Resource>				m_vertexBuffer;
		//Microsoft::WRL::ComPtr<ID3D12Resource>				m_indexBuffer;
		//Microsoft::WRL::ComPtr<ID3D12Resource>				m_constantBuffer;
		//ModelViewProjectionConstantBuffer						m_constantBufferData;
		//UINT8*												m_mappedConstantBuffer;
		//UINT													m_cbvDescriptorSize;
		//D3D12_RECT											m_scissorRect;
		//std::vector<byte>										m_vertexShader;
		//std::vector<byte>										m_pixelShader;
		//D3D12_VERTEX_BUFFER_VIEW								m_vertexBufferView;
		//D3D12_INDEX_BUFFER_VIEW								m_indexBufferView;


		// ������Ⱦѭ���ı�����
	uint32_t    frameCount;
	bool		m_loadingComplete;
	float		m_radiansPerSecond;
	float		m_angle;
	bool		m_tracking;
};
}