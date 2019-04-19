#pragma once
#include "Singleton.h"

class GameObject;
class CameraManager :
	public Singleton<CameraManager>
{
private:

	Vector3 position;
	Vector3 endScale;
	Vector3 scale;

	Matrix projection;
	Matrix view;

	Vector3 viewSize;

	float angle;

	bool lockInMap = false;
public:
	CameraManager();
	virtual ~CameraManager();

	void SetTransform();
	void Update();

	void SetViewMatrix(Matrix* out, Vector3 position, Vector3 scale, float angle);

	void Init();

public:

	GameObject * targetObject;
	RECT		 mapRange;

	float		 moveSpeed	= 300.0f;
	float		 shakeTime	= 0.0f;
	float		 shakePower	= 0.0f;

	void SetTarget(GameObject* tar) { targetObject = tar; }
	void SetSpeed(float speed) { moveSpeed = speed; }
	void SetRange(float left = 0, float top = 0, float right = 0, float bottom = 0);
	void SetLerpScale(float lsca);
	void SetScale(float sca);

	// 카메라 흔들기
	void Shake(float sec, float power);
	// 거리에 따른 카메라 흔들림 조정
	void distanceShake(Vector3 epicenter, float sec, float power);
	void PlusScale(float plus);

	Vector3 GetPosition() { return position; }
	void SetPosition(const Vector3& pos) { position = pos; }

	void ScrollToScreen(Vector3* posit);
};

#define CAMERA (*CameraManager::Instance())