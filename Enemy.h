#pragma once
#include "LifeUnit.h"

class Gun;
class Enemy :
	public LifeUnit
{
protected:
	GameObject* m_target;

	Texture* m_attack;
	Texture* m_walk;
	Texture* m_death;

	INT m_frameChangeSpeed = 50;

	INT m_damage;

	bool m_isOnPlayer = false;

	Gun* m_gun = nullptr;

	float m_attackRange;

public:
	Enemy(GameObject* target)
		: LifeUnit(OBJKIND::OBJ_ENEMY), m_target(target) { position = V3ZERO; }

	Enemy(Vector3 position, GameObject* target)
		: LifeUnit(OBJKIND::OBJ_ENEMY), m_target(target) { GameObject::position = position; }

	Enemy(float x, float y, float z, GameObject* target)
		: Enemy(Vector3(x, y, z), target) {}

	virtual ~Enemy() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	virtual void OnDamage(int damage) override;

	void PushOtherEnemy(Collider* col);

	virtual void WalkUpdate();
	virtual void DeathUpdate();
	virtual void AttackUpdate();
};

