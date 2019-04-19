#pragma once
#include "Bullet.h"

class LifeUnit;
class LaserBullet :
	public Bullet
{
private:
	GameObject * owner = nullptr;

	Vector3 offset;

	float spawnDelay;
public:
	LaserBullet(GameObject * owner, const string& owner_tag, Vector3 start, Vector3 dir, float damage);
	~LaserBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;
};

