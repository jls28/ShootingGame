#pragma once
#include "Bullet.h"


// 시간이 없어서 얜 적이 쏘는 총알만 가능
// 플레이어는 못씀

class DownBullet :
	public Bullet
{
private:
	float endY;
	float ringSpawnTime;

	const float ringDelay = 200;

	Texture* warningEft = nullptr;

	Frame warningFrame;
public:
	DownBullet(Vector3 position, float height, float speed, float damage);
	~DownBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

