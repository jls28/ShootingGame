#pragma once
#include "GameObject.h"
class GageBar2 :
	public GameObject
{
private:
	Vector3 targetPos;
	int maxHp;
	int curHp;
	float contraWidth;
	float width;

	Vector3 offset;

	Vector3 infoSize;

	int imgCnt;
public:
	GageBar2(const string& texture, Vector3 target, int max, int cur, Vector3 offset = V3ZERO);
	virtual ~GageBar2();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;


	void Setting(int max, int cur) { maxHp = max; curHp = cur; }
};

