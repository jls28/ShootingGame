#pragma once
#include "Gun.h"
class Spread :
	public Gun
{
public:
	Spread(GameObject* owner, Vector3 position);
	virtual ~Spread();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	virtual void Fire(Vector3 destination, int key = AUTO_SHOT) override;

	void FireNWayBullet(float theta, Vector3 pivotVec, int n);
};

