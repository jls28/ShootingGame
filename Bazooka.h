#pragma once
#include "Gun.h"


class Bazooka :
	public Gun
{
public:
	Bazooka(GameObject* owner, Vector3 position);
	virtual ~Bazooka();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	virtual void Fire(Vector3 destination, int key = AUTO_SHOT) override;
};

