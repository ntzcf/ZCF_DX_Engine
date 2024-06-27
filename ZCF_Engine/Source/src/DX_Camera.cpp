#include "GameLogic/DX_Camera.h"

using namespace DirectX;

namespace Engine::GameLogic::camera
{


	DX_Camera::DX_Camera()
	{
		SetLens(0.25f * XM_PI, 1.0f, 1.0f, 1000.0f);
	}

	DX_Camera::~DX_Camera()
	{
	}

	XMVECTOR DX_Camera::GetPosition()const
	{
		return XMLoadFloat3(&mPosition);
	}

	XMFLOAT3 DX_Camera::GetPosition3f()const
	{
		return mPosition;
	}

	void DX_Camera::SetPosition(float x, float y, float z)
	{
		mPosition = XMFLOAT3(x, y, z);
		mViewDirty = true;
	}

	void DX_Camera::SetPosition(const XMFLOAT3& v)
	{
		mPosition = v;
		mViewDirty = true;
	}

	XMVECTOR DX_Camera::GetRight()const
	{
		return XMLoadFloat3(&mRight);
	}

	XMFLOAT3 DX_Camera::GetRight3f()const
	{
		return mRight;
	}

	XMVECTOR DX_Camera::GetUp()const
	{
		return XMLoadFloat3(&mUp);
	}

	XMFLOAT3 DX_Camera::GetUp3f()const
	{
		return mUp;
	}

	XMVECTOR DX_Camera::GetLook()const
	{
		return XMLoadFloat3(&mLook);
	}

	XMFLOAT3 DX_Camera::GetLook3f()const
	{
		return mLook;
	}

	float DX_Camera::GetNearZ()const
	{
		return mNearZ;
	}

	float DX_Camera::GetFarZ()const
	{
		return mFarZ;
	}

	float DX_Camera::GetAspect()const
	{
		return mAspect;
	}

	float DX_Camera::GetFovY()const
	{
		return mFovY;
	}

	float DX_Camera::GetFovX()const
	{
		float halfWidth = 0.5f * GetNearWindowWidth();
		return 2.0f * atan(halfWidth / mNearZ);
	}

	float DX_Camera::GetNearWindowWidth()const
	{
		return mAspect * mNearWindowHeight;
	}

	float DX_Camera::GetNearWindowHeight()const
	{
		return mNearWindowHeight;
	}

	float DX_Camera::GetFarWindowWidth()const
	{
		return mAspect * mFarWindowHeight;
	}

	float DX_Camera::GetFarWindowHeight()const
	{
		return mFarWindowHeight;
	}

	void DX_Camera::SetLens(float fovY, float aspect, float zn, float zf)
	{
		// cache properties
		mFovY = fovY;
		mAspect = aspect;
		mNearZ = zn;
		mFarZ = zf;

		mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f * mFovY);
		mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f * mFovY);

		XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
		XMStoreFloat4x4(&mProj, P);
	}

	void DX_Camera::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
	{
		XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
		XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
		XMVECTOR U = XMVector3Cross(L, R);

		XMStoreFloat3(&mPosition, pos);
		XMStoreFloat3(&mLook, L);
		XMStoreFloat3(&mRight, R);
		XMStoreFloat3(&mUp, U);

		mViewDirty = true;
	}

	void DX_Camera::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
	{
		XMVECTOR P = XMLoadFloat3(&pos);
		XMVECTOR T = XMLoadFloat3(&target);
		XMVECTOR U = XMLoadFloat3(&up);

		LookAt(P, T, U);

		mViewDirty = true;
	}

	XMMATRIX DX_Camera::GetView()const
	{
		assert(!mViewDirty);
		return XMLoadFloat4x4(&mView);
	}

	XMMATRIX DX_Camera::GetProj()const
	{
		return XMLoadFloat4x4(&mProj);
	}


	XMFLOAT4X4 DX_Camera::GetView4x4f()const
	{
		assert(!mViewDirty);
		return mView;
	}

	XMFLOAT4X4 DX_Camera::GetProj4x4f()const
	{
		return mProj;
	}

	void DX_Camera::Strafe(float d)
	{
		// mPosition += d*mRight
		XMVECTOR s = XMVectorReplicate(d);
		XMVECTOR r = XMLoadFloat3(&mRight);
		XMVECTOR p = XMLoadFloat3(&mPosition);
		XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, r, p));

		mViewDirty = true;
	}

	void DX_Camera::Walk(float d)
	{
		// mPosition += d*mLook
		XMVECTOR s = XMVectorReplicate(d);
		XMVECTOR l = XMLoadFloat3(&mLook);
		XMVECTOR p = XMLoadFloat3(&mPosition);
		XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, l, p));

		mViewDirty = true;
	}

	void DX_Camera::Pitch(float angle)
	{
		// Rotate up and look vector about the right vector.

		XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);

		XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
		XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));

		mViewDirty = true;
	}

	void DX_Camera::Yaw(float angle)
	{
		// Rotate the basis vectors about the world y-axis.

		XMMATRIX R = XMMatrixRotationY(angle);

		XMStoreFloat3(&mRight, XMVector3TransformNormal(XMLoadFloat3(&mRight), R));
		XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
		XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));

		mViewDirty = true;
	}

	void DX_Camera::UpdateViewMatrix()
	{
		if (mViewDirty)
		{
			XMVECTOR R = XMLoadFloat3(&mRight);
			XMVECTOR U = XMLoadFloat3(&mUp);
			XMVECTOR L = XMLoadFloat3(&mLook);
			XMVECTOR P = XMLoadFloat3(&mPosition);

			// Keep camera's axes orthogonal to each other and of unit length.
			L = XMVector3Normalize(L);
			U = XMVector3Normalize(XMVector3Cross(L, R));

			// U, L already ortho-normal, so no need to normalize cross product.
			R = XMVector3Cross(U, L);

			// Fill in the view matrix entries.
			float x = -XMVectorGetX(XMVector3Dot(P, R));
			float y = -XMVectorGetX(XMVector3Dot(P, U));
			float z = -XMVectorGetX(XMVector3Dot(P, L));

			XMStoreFloat3(&mRight, R);
			XMStoreFloat3(&mUp, U);
			XMStoreFloat3(&mLook, L);

			mView(0, 0) = mRight.x;
			mView(1, 0) = mRight.y;
			mView(2, 0) = mRight.z;
			mView(3, 0) = x;

			mView(0, 1) = mUp.x;
			mView(1, 1) = mUp.y;
			mView(2, 1) = mUp.z;
			mView(3, 1) = y;

			mView(0, 2) = mLook.x;
			mView(1, 2) = mLook.y;
			mView(2, 2) = mLook.z;
			mView(3, 2) = z;

			mView(0, 3) = 0.0f;
			mView(1, 3) = 0.0f;
			mView(2, 3) = 0.0f;
			mView(3, 3) = 1.0f;

			mViewDirty = false;
		}
	}
}







const float MathHelper::Infinity = FLT_MAX;
const float MathHelper::Pi = 3.1415926535f;

float MathHelper::AngleFromXY(float x, float y)
{
	float theta = 0.0f;

	// Quadrant I or IV
	if (x >= 0.0f)
	{
		// If x = 0, then atanf(y/x) = +pi/2 if y > 0
		//                atanf(y/x) = -pi/2 if y < 0
		theta = atanf(y / x); // in [-pi/2, +pi/2]

		if (theta < 0.0f)
			theta += 2.0f * Pi; // in [0, 2*pi).
	}

	// Quadrant II or III
	else
		theta = atanf(y / x) + Pi; // in [0, 2*pi).

	return theta;
}

XMVECTOR MathHelper::RandUnitVec3()
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR Zero = XMVectorZero();

	// Keep trying until we get a point on/in the hemisphere.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3.
		XMVECTOR v = XMVectorSet(MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), 0.0f);

		// Ignore points outside the unit sphere in order to get an even distribution 
		// over the unit sphere.  Otherwise points will clump more on the sphere near 
		// the corners of the cube.

		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		return XMVector3Normalize(v);
	}
}

XMVECTOR MathHelper::RandHemisphereUnitVec3(XMVECTOR n)
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR Zero = XMVectorZero();

	// Keep trying until we get a point on/in the hemisphere.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3.
		XMVECTOR v = XMVectorSet(MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), 0.0f);

		// Ignore points outside the unit sphere in order to get an even distribution 
		// over the unit sphere.  Otherwise points will clump more on the sphere near 
		// the corners of the cube.

		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		// Ignore points in the bottom hemisphere.
		if (XMVector3Less(XMVector3Dot(n, v), Zero))
			continue;

		return XMVector3Normalize(v);
	}
}