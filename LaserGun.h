#pragma once
#include "Gun.h"
class LaserGun :
	public Gun
{
public:
	LaserGun(GameObject* owner, Vector3 position);
	virtual ~LaserGun();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	virtual void Fire(Vector3 destination, int key = AUTO_SHOT) override;
};

