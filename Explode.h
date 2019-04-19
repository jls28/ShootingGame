#pragma once
#include "GameObject.h"
class Explode :
	public GameObject
{
private:
	string shooter;

	bool endAttack;
	float damage;
public:
	Explode(Vector3 position, const string& shooter, float size, float damage);
	~Explode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;
};

