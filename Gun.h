#pragma once
#include "GameObject.h"

#define AUTO_SHOT -1

class Gun :
	public GameObject
{
protected:

	int m_maxBullet = 0;
	int m_curBullet = 0;

	float m_maxReloadDelay = 0;
	float m_maxShotDelay = 0;

	float m_frameSkip = 0;

	float m_gunLength = 0;
	float m_rebound = 10;
	float m_bulletSpeed;

	GameObject* m_owner;
	Vector3 m_direction;
	Vector3 m_destination;

	bool m_reload = false;

	string bulletEft;
	string ringEft;

	int m_damage;

public:
	Gun();
	virtual ~Gun();

	virtual void Init	() override;
	virtual void Update	() override;
	virtual void Render	() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	virtual void Fire(Vector3 destination, int key = AUTO_SHOT) PURE;

	Vector3 GetFirePos(float rot);
	Vector3 GetDirection(float rebound, Vector3 destination);
	bool	CanFire();
	bool	IsReload() { return m_reload; }
	bool	AutoGeneric(Vector3 destination, int key = AUTO_SHOT);

	float GetRotation(Vector3 dir);

	void DrawInfo(const string& gunName);
	void DrawLaser();

	void GunSetting(float shotDelay, float reloadDelay, int maxBullet, int length, int rebound);

	void SetDamage(int dam) { m_damage = dam; }

	int GetMaxBullet()
	{
		return m_maxBullet;
	}
	int GetCurBullet()
	{
		return m_curBullet;
	}

	void SetBulletTexture(const string& bulletEft, const string& ringEft);
	void SetBulletSpeed(float spd) { m_bulletSpeed = spd; }
};