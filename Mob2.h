#pragma once
#include "Enemy.h"
class Mob2 :
	public Enemy
{
private:
	float shotDelay;
public:
	Mob2(Vector3 start, GameObject* target) : Enemy(start, target) {}
	Mob2(float x, float y, GameObject* target) : Enemy(x, y, 0, target) {}
	virtual ~Mob2();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;
	virtual void AttackUpdate();

};

