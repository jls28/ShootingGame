#pragma once
#include "Bullet.h"



class NormalBullet :
	public Bullet
{
protected:
	float ringSpawnTime;

	const float ringDelay = 60;

	string eftImg;
	string eftSound;

	// º®ÀÌ¶û ºÎµú
	string wallImg;
	// ÀûÀÌ¶û ºÎµú
	string targetImg;
public:
	NormalBullet(const string& shooter_tag, Vector3 start, Vector3 dir, float speed, float damage);
	virtual ~NormalBullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
	
	virtual void OnCollision(Collider* col) override;

	void TextureSet(const string& bulletImg, const string& eftImg);
	void SoundSet(const string& eftSound);

	void CollideSet(const string& wall, const string& target);
};

