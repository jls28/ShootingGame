#pragma once
#include "GameObject.h"

// 포물선 이동을 계산해주는 객체

// Setting() 함수 사용으로 시작과 끝 지점, 속도 결정 가능
// 사용시 이 객체를 상속받고 매 프레임 IsEnd() 함수로 검사하면 끝났는지 확인 가능

class Parabola :
	public GameObject
{
private:
	Vector3 startPos;
	Vector3 endPos;
	Vector3 destPos;
	Vector3 speed;

	float gravity = 0.f;
	float destTime = 0.f;
	float height = 0.f;
	float destHeight = 0.f;
	float accrueTime = 0.f;
	float maxHeight = 0.f;
	float maxAchieveTime = 0.f;

public:
	Parabola(OBJKIND kind);
	~Parabola();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setting(Vector3 start, Vector3 dest, float maxTime, float plusHeight);
	void PreCalculate();

	bool IsEnd();
};

