#pragma once
#include "GameObject.h"
class SpawnEffect :
	public GameObject
{
private:
	GameObject* m_object;

	int m_cycle = 0;
	int m_curFrame = 0;
	int m_endCycle = 2;
public:
	SpawnEffect(GameObject* obj, int cycle = 2, Vector3 position = V3ZERO, const string& text = "SPAWN_EFT");
	virtual ~SpawnEffect();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;
};

