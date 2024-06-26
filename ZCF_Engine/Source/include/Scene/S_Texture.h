#pragma once

namespace Engine::scene::Texture
{
	enum  RBR_Texture_Attributes
	{
		Albedo,		//		(R,G,B)��ԭɫ�ķ�����
		Normal,
		Metallic,	//		������	:	���淴�� �� ������ ��ǿ�ȷ���
		Roughness,	//		�ֲڶ�	:	���仨�귶Χ,���䴿��		
		Hegiht,
		F0,			//		0��ǵ�Frenel  ���淴���		������:1-F0	   �������:һ��0,02 �� 0.05 ���ֱ仯С����
		//		����ֱ�Ӳ�����ʵ���ݲ���
		AO,
		BRDF		//		Ԥ������ͼ   (Frenel,Roughness)
	};
}