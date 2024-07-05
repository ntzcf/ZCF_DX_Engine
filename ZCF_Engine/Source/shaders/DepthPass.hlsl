
// 常量缓冲区结构，用于存储从CPU传递到GPU的变换矩阵  

cbuffer WorldViewProjMatrix : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Proj;
}
  
float4 VS(float3 position : POSITION)
{
    return mul(mul(mul(float4(position, 1.0f), World), View), Proj);
}
 
void PS(float4 Positon) : SV_TARGET
{
    
}