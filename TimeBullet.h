#pragma once
#include "Bullet.h"

class LifeUnit;
class TimeBullet :
	public Bullet
{
private:
	Vector3 endPos;

	std::map<LifeUnit*, float> targetDelay;

	float delTime;

	// º®ÀÌ¶û ºÎµú
	string wallImg;
	// ÀûÀÌ¶û ºÎµú
	string targetImg;
public:
	TimeBullet(const string& owner_tag, Vector3 start, Vector3 dir, float speed, float damage, float delTime);
	virtual ~TimeBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	void CollideSet(const string& wall, const string& target);
};

