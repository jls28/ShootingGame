#pragma once
#include "Enemy.h"


class Gun;
class Boss :
	public Enemy
{
protected:
	Texture* m_rush;
	
	float m_cameraTime;
	float m_shotDelay = 0;

	float m_rushRange;

	Gun* m_gun2;

	int m_nowGunMode;

public:
	Boss(float x,float y, GameObject* target);
	virtual ~Boss();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	virtual void OnDamage(int damage) override;
	virtual void AttackUpdate();
	virtual void DeathUpdate();

	void FocusUpdate();

	void RushUpdate();
};

