#include "DXUT.h"
#include "Bazooka.h"

#include "BazookaBullet.h"

Bazooka::Bazooka(GameObject * owner, Vector3 position)
{
	m_owner = owner;
	GameObject::position = position;
}

Bazooka::~Bazooka()
{
}

void Bazooka::Init()
{
	GunSetting(850, 1500, 3, 0, 0);
	SetTag("BAZOOKA");
	SetCenter(Vector3(0, 0, 0));

	m_bulletSpeed = 1200;
}

void Bazooka::Update()
{
	Gun::Update();
}

void Bazooka::Render()
{
	DrawInfo("BAZOOKA");
}

void Bazooka::Destroy()
{
}

void Bazooka::OnCollision(Collider * col)
{
}

void Bazooka::Fire(Vector3 destination, int key)
{
	if (AutoGeneric(destination, key))
	{
		Vector3 p = GetFirePos(rotation);

		CAMERA.distanceShake(position, 350, 13);

		Vector3 d = GetDirection(m_rebound, destination);

		auto bullet = Instantiate(BazookaBullet(m_owner->tag, p, d, m_bulletSpeed, 100));

		bullet->TextureSet(bulletEft, ringEft);
		bullet->SoundSet("BAZOOKA_END");

		SOUND.DuplicateDistancePlay("BAZOOKA_SHOT", position);
	}
}

