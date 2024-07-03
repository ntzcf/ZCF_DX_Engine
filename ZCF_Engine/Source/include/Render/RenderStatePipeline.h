#include<tchar.h>

#include "d3dUtil.h"

#include "Scene/Materials.h"

namespace Engine::Render::renderpass
{
	using namespace Engine::scene::Materials;
	//				PSO
	enum ShaderType
	{
		VS,
		PS,

		DS,
		HS,
		GS,//	Geometry

		MS,//	Mesh Shader
		
		CS,
		//	更多先进的着色器模型
	};

	struct Shader
	{
		ShaderType		ShaderType;
		std::string		ShaderPath;
		std::string		ShaderVersion;
		std::string		ShaderMain;
		//使用时候注意;用	string.c_str()	转换
		uint16_t		ShaderFlags1;
		uint16_t		ShaderFlags2;
	};

	struct MutiSample
	{
		uint32_t Mask = 0xffff;
		uint32_t Count = 1;
		uint32_t Quality = 0;
	};

	enum BlendState
	{
		DefaultBlend,
	};

	enum Topology
	{
		Undefined,
		Point,
		Line,
		Triangle,
		Patch,
	};

	struct InputElementView
	{
		InputElementView(const char* SemanticName,
		uint32_t						SemanticIndex,
		DXGI_FORMAT						Format,
		uint32_t						InputSlot,
		uint32_t						AlignedByteOffset,
		bool							IsInstance,
		uint32_t						InstanceDataStepRate)
		:
		SemanticName(SemanticName),
		SemanticIndex(SemanticIndex),
		Format(Format),
		InputSlot(InputSlot),
		AlignedByteOffset(AlignedByteOffset),
		IsInstance(IsInstance),
		InstanceDataStepRate(InstanceDataStepRate)
		{}
		//	使用的时候再 c_str()转成LPCSTR							
		const char* 					SemanticName;
		uint32_t						SemanticIndex;
		DXGI_FORMAT						Format;
		uint32_t						InputSlot;
		uint32_t						AlignedByteOffset;
		bool							IsInstance;
		uint32_t						InstanceDataStepRate;
	};

	//const InputElementView DepthStreamInputView(std::string("position"), 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, 0, 0);

	enum FillMode
	{
		WireFrame = 2,
		Solid = 3
	};

	enum CullMode
	{
		None = 1,
		Front = 2,
		Back = 3
	};

	struct Rasterize
	{
		
		FillMode			               FillMode=FillMode::Solid;
		CullMode			               CullMode=CullMode::Back;
		BOOL                               FrontCounterClockwise=1;
	};


	//		Sample	Blend	InputView		Topology	IsStreamOut


	struct  RenderPSO
	{
	public:
		
		Shader									Shader;
		Rasterize								Rasterize;
		std::vector<InputElementView>			InputView;
		MutiSample								MutiSample;
		BlendState								BlendState=BlendState::DefaultBlend;
		Topology								Topolopy=Topology::Triangle;

	};
}