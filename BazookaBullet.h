#pragma once
#include "NormalBullet.h"


class BazookaBullet :
	public NormalBullet
{
public:
	BazookaBullet(const string& shooter_tag, Vector3 start, Vector3 dir, float speed, float damage);
	virtual ~BazookaBullet();
	
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
	
	virtual void OnCollision(Collider* col) override;

};

