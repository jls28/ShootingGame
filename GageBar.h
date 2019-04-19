#pragma once
#include "GameObject.h"
class GageBar :
	public GameObject
{
private:
	Vector3 & targetPos;
	int &maxHp;
	int &curHp;
	float contraWidth;
	float width;

	Vector3 offset;

	Vector3 infoSize;

	int imgCnt;
public:
	GageBar(const string& texture, Vector3 &target, int& max, int&cur, Vector3 offset = V3ZERO);
	virtual ~GageBar();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

};

