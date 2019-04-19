#pragma once
#include "GameObject.h"

// ������ �̵��� ������ִ� ��ü

// Setting() �Լ� ������� ���۰� �� ����, �ӵ� ���� ����
// ���� �� ��ü�� ��ӹް� �� ������ IsEnd() �Լ��� �˻��ϸ� �������� Ȯ�� ����

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

