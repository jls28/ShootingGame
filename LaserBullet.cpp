#include "DXUT.h"
#include "LaserBullet.h"

#include "Texture.h"
#include "LifeUnit.h"

#include "TimeBullet.h"

#define LASER_RED_SCALE 3

LaserBullet::LaserBullet(GameObject * owner, const string& owner_tag, Vector3 start, Vector3 dir, float damage)
	: Bullet(owner_tag, start, dir, 0, damage), owner(owner)
{
	rotation = owner->rotation;

	offset = start - owner->position;
}

LaserBullet::~LaserBullet()
{
}

void LaserBullet::Init()
{
	if (m_shooter == "PLAYER")
		SetTexture("LASER_EFT");
	else if(m_shooter == "ENEMY")
		SetTexture("BOSS_LASER_EFT");

	SetCenter(Vector3(20, 31, 0));
	SetScale(Vector3(LASER_RED_SCALE, LASER_RED_SCALE, 0));

	UseFrame(0, 11, 80);
	UseCollider(500);
	SetRenderLayer(1);

	spawnDelay = 0;
}

void LaserBullet::Update()
{
	SetPosition(owner->position + offset);

	if (spawnDelay <= GetNowTime())
	{
		if (m_frame.nowFrame < 8) {
			auto bullet = Instantiate(TimeBullet(m_shooter, position, m_direcition, 700, 35, GetNowTime() + 600));

			if (m_shooter == "PLAYER")
				bullet->CollideSet("BLUE_W_EFT", "BLUE_T_EFT");
			else if (m_shooter == "ENEMY")
				bullet->CollideSet("RED_W_EFT", "RED_T_EFT");

		}
		spawnDelay = GetNowTime() + 150;
	}

	if (m_frame.nowFrame == m_frame.endFrame)
	{
		Kill();
	}
}

void LaserBullet::Render()
{
}

void LaserBullet::Destroy()
{
}

void LaserBullet::OnCollision(Collider * col)
{
	
}
