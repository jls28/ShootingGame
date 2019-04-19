#include "DXUT.h"
#include "CameraManager.h"

#include "GameObject.h"

CameraManager::CameraManager()
{
	Init();
}


CameraManager::~CameraManager()
{
}

void CameraManager::SetTransform()
{
	g_pDevice->SetTransform(D3DTS_VIEW, &view);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &projection);
}

void CameraManager::Update()
{
	D3DXVec3Lerp(&scale, &scale, &endScale, GetDeltaTime() * 10);

	if (shakeTime >= GetNowTime())
	{
		position += Vector3(INPUT.GetRandom(-shakePower, shakePower),
			INPUT.GetRandom(-shakePower, shakePower), 0);
	}

	if (targetObject)
		D3DXVec3Lerp(&position, &position, &targetObject->position, GetDeltaTime() * 5);

	if (lockInMap)
	{
		const int wx = WINSIZEX;
		const int wy = WINSIZEY;

		if (position.x - wx / 2 < mapRange.left)
			position.x = mapRange.left + wx / 2;
		if (position.x + wx / 2 > mapRange.right)
			position.x = mapRange.right - wx / 2;
		if (position.y - wy / 2 < mapRange.top)
			position.y = mapRange.top + wy / 2;
		if (position.y + wy / 2 > mapRange.bottom)
			position.y = mapRange.bottom - wy / 2;
	}

	SetViewMatrix(&view, position, scale, angle);
}

void CameraManager::SetViewMatrix(Matrix* out, Vector3 position, Vector3 scale, float angle)
{
	*out = D3DXMATRIX(
		scale.x * cosf(angle), scale.x * sinf(angle), 0, 0,
		-scale.y * sinf(angle), scale.y * cosf(angle), 0, 0,
		0, 0, scale.z, 0,
		-position.x * scale.y * cosf(angle) + position.y * scale.y * sinf(angle),
		-position.x * scale.x * sinf(angle) - position.y * scale.y * cosf(angle), 0, 1);
}

void CameraManager::Init()
{
	targetObject = nullptr;
	position = V3CENTER;
	scale = endScale = Vector3(1, 1, 1);

	viewSize = Vector3(WINSIZEX, WINSIZEY, 0);

	angle = 0.0f;
	moveSpeed = 300.0f;

	D3DXMatrixOrthoLH(&projection, viewSize.x, -viewSize.y, 0, 1);
}

void CameraManager::SetRange(float left, float top, float right, float bottom)
{
	if (left == 0 && right == 0 && top == 0 && bottom == 0)
		lockInMap = false;

	mapRange.left = left;
	mapRange.right = right;
	mapRange.top = top;
	mapRange.bottom = bottom;

	lockInMap = true;
}

void CameraManager::Shake(float sec, float power)
{
	if (shakePower < power) {
		shakeTime = max(shakeTime, sec + GetNowTime());
		shakePower = power;
	}
	else
	{
		if (shakeTime <= GetNowTime())
		{
			shakeTime = sec + GetNowTime();
			shakePower = power;
		}
	}
}

void CameraManager::distanceShake(Vector3 epicenter, float sec, float power)
{
	Vector3 length = epicenter - position;

	float range = D3DXVec3Length(&length);

	float red = 0;

	if (range >= 1333)
		return;
	else if (range >= 999)
		red = 0.3;
	else if (range >= 666)
		red = 0.6;
	else if (range >= 333)
		red = 0.9;
	else
		red = 1.0;



	Shake(sec * red, power * red);
}

void CameraManager::PlusScale(float plus)
{
	endScale.x += plus;
	endScale.y += plus;
}

void CameraManager::ScrollToScreen(Vector3 * posit)
{
	*posit -= (position - V3CENTER);
}

void CameraManager::SetScale(float sca)
{
	scale.x = endScale.x = sca;
	scale.y = endScale.y = sca;
}

void CameraManager::SetLerpScale(float lsca)
{
	endScale.x = lsca;
	endScale.y = lsca;
}
