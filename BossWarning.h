#pragma once
#include "GameObject.h"
class BossWarning :
	public GameObject
{
private:
	Texture* onoff;

	Texture* bossWarnings;

	Vector3 poses[4];

	float destTime;
public:
	BossWarning();
	virtual ~BossWarning();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;


};

