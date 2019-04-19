#pragma once
#include "Enemy.h"
class Mob1 :
	public Enemy
{
private:

public:
	Mob1(Vector3 start, GameObject* target) : Enemy(start, target) {}
	Mob1(float x, float y, GameObject* target) : Enemy(x, y, 0, target) {}
	virtual ~Mob1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;
};

