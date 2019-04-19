#include "DXUT.h"
#include "LaserGun.h"

#include "LaserBullet.h"
#include "ScreenEffect.h"


LaserGun::LaserGun(GameObject * owner, Vector3 position)
{
	m_owner = owner;
	SetPosition(position);
}

LaserGun::~LaserGun()
{
}

void LaserGun::Init()
{
	GunSetting(900, 2000, 6, 55, 0);
	SetTag("LASER");
	SetCenter(Vector3(0, 0, 0));
}

void LaserGun::Update()
{
	Gun::Update();
}

void LaserGun::Render()
{
	DrawInfo("LASER GUN");
}

void LaserGun::Destroy()
{

}

void LaserGun::OnCollision(Collider * col)
{

}

void LaserGun::Fire(Vector3 destination, int key)
{
	if (AutoGeneric(destination, key)) {

		Vector3 d = GetDirection(m_rebound, destination);
		Vector3 p = GetFirePos(rotation);

		CAMERA.distanceShake(position, 300, 12);

		Instantiate(LaserBullet(this, m_owner->tag, p, d, 50));

		if (m_owner->tag == "PLAYER") {
			if (ScreenEffect::screenEftCount < 2)
				Instantiate(ScreenEffect(IMAGE.GetImage("SCREEN_EFT1")));
		}

		SOUND.DuplicateDistancePlay("LASER", position, 95);
	}
}
