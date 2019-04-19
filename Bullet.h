#pragma once
#include "GameObject.h"
class Bullet :
	public GameObject
{
protected:
	Vector3 m_direcition;
	float m_speed;
	float m_damage;

	string m_shooter;
public:
	Bullet(const string& shooter_tag, Vector3 start, Vector3 dir, float speed, float damage);
	virtual ~Bullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;
};

