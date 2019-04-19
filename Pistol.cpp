#include "DXUT.h"
#include "Pistol.h"

#include "NormalBullet.h"


Pistol::Pistol(GameObject * owner, Vector3 position)
{
	m_owner = owner;
	SetPosition(position);
}

Pistol::~Pistol()
{
}

void Pistol::Init()
{
	GunSetting(175, 1500, 25, 40, 5);
	SetTag("PISTOL");
	SetCenter(Vector3(0, 0, 0));
	m_bulletSpeed = 1000;
	m_damage = 30;
}

void Pistol::Update()
{
	Gun::Update();
}

void Pistol::Render()
{
	DrawInfo("PISTOL");
}

void Pistol::Destroy()
{
}

void Pistol::OnCollision(Collider * col)
{
}

void Pistol::Fire(Vector3 destination, int key)
{
	if (AutoGeneric(destination, key)) {

		Vector3 d = GetDirection(m_rebound, destination);
		Vector3 p = GetFirePos(rotation);

		CAMERA.distanceShake(position, 100, 4);
		auto bullet = Instantiate(NormalBullet(m_owner->tag, p, d, m_bulletSpeed, m_damage));

		bullet->TextureSet(bulletEft, ringEft);

		if (m_owner->tag == "PLAYER") {
			bullet->CollideSet("BLUE_W_EFT", "BLUE_T_EFT");
			SOUND.DuplicateDistancePlay("PISTOL", position, 100);
		}
		else if (m_owner->tag == "ENEMY")
		{
			bullet->CollideSet("RED_W_EFT", "RED_T_EFT");
			SOUND.DuplicateDistancePlay("PISTOL", position, 85);
		}
	}
}