#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <d3d12.h>
#include <DirectXMath.h>


class MathHelper
{
public:
	// Returns random float in [0, 1).
	static float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Returns random float in [a, b).
	static float RandF(float a, float b)
	{
		return a + RandF() * (b - a);
	}

	static int Rand(int a, int b)
	{
		return a + rand() % ((b - a) + 1);
	}

	template<typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	static T Lerp(const T& a, const T& b, float t)
	{
		return a + (b - a) * t;
	}

	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}

	// Returns the polar angle of the point (x,y) in [0, 2*PI).
	static float AngleFromXY(float x, float y);

	static DirectX::XMVECTOR SphericalToCartesian(float radius, float theta, float phi)
	{
		return DirectX::XMVectorSet(
			radius * sinf(phi) * cosf(theta),
			radius * cosf(phi),
			radius * sinf(phi) * sinf(theta),
			1.0f);
	}

	static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out 
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		DirectX::XMMATRIX A = M;
		A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
		return DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, A));
	}

	static DirectX::XMFLOAT4X4 Identity4x4()
	{
		static DirectX::XMFLOAT4X4 I(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return I;
	}

	static DirectX::XMVECTOR RandUnitVec3();
	static DirectX::XMVECTOR RandHemisphereUnitVec3(DirectX::XMVECTOR n);

	static const float Infinity;
	static const float Pi;


};

namespace Engine::GameLogic::camera
{

	class DX_Camera
	{
	public:
		DX_Camera();
		~DX_Camera();

		//Get及Set世界空间下摄像机的位置
		DirectX::XMVECTOR GetPosition()const;
		DirectX::XMFLOAT3 GetPosition3f()const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const DirectX::XMFLOAT3& v);

		//获取摄像机的基向量（观察空间的三个轴在世界空间下的表示）
		DirectX::XMVECTOR GetRight()const;
		DirectX::XMFLOAT3 GetRight3f()const;
		DirectX::XMVECTOR GetUp()const;
		DirectX::XMFLOAT3 GetUp3f()const;
		DirectX::XMVECTOR GetLook()const;
		DirectX::XMFLOAT3 GetLook3f()const;

		//获取视锥体属性
		float GetNearZ()const;//近裁剪面距离
		float GetFarZ()const;//远裁剪面距离
		float GetAspect()const;//视口纵横比
		float GetFovY()const;//垂直视场角
		float GetFovX()const;//水平视场角

		//获取用观察空间坐标表示的近、远平面大小
		float GetNearWindowWidth()const;
		float GetNearWindowHeight()const;
		float GetFarWindowWidth()const;
		float GetFarWindowHeight()const;

		//赋值视锥体变量，设置投影矩阵(实现使用了内置函数XMMatrixPerspectiveFovLH)
		void SetLens(float fovY, float aspect, float zn, float zf);

		//准备观察矩阵数据
		void LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp);
		void LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up);

		//获取观察矩阵和投影矩阵
		DirectX::XMMATRIX GetView()const;
		DirectX::XMMATRIX GetProj()const;
		DirectX::XMFLOAT4X4 GetView4x4f()const;
		DirectX::XMFLOAT4X4 GetProj4x4f()const;

		//将摄像机按距离d左右平移（Strafe）或前后移动（Walk）
		void Strafe(float distance);//左右平移摄像机
		void Walk(float distance);//前后推拉摄像机

		//旋转摄像机
		void Pitch(float angle);//Pitch方向
		void Yaw(float angle);//Yaw方向

		//修改摄像机的位置和朝向后，调用此函数来重新构建观察矩阵
		void UpdateViewMatrix();

	private:
		//摄像机坐标系（三个轴的基向量）在世界空间下的坐标
		DirectX::XMFLOAT3 mPosition = { 0.0f, 0.0f, 0.0f };
		DirectX::XMFLOAT3 mRight = { 1.0f, 0.0f, 0.0f };
		DirectX::XMFLOAT3 mUp = { 0.0f, 1.0f, 0.0f };
		DirectX::XMFLOAT3 mLook = { 0.0f, 0.0f, 1.0f };

		//视锥体属性
		float mNearZ = 0.0f;
		float mFarZ = 0.0f;
		float mAspect = 0.0f;
		float mFovY = 0.0f;
		float mNearWindowHeight = 0.0f;
		float mFarWindowHeight = 0.0f;

		bool mViewDirty = true;

		//观察矩阵和投影矩阵
		DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
		DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
	};
}
#endif // !CAMERA_H