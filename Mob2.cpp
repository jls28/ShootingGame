#include "DXUT.h"
#include "Mob2.h"

#include "MapViewer.h"
#include "Pistol.h"
#include "SpawnEffect.h"
#include "DownBullet.h"

Mob2::~Mob2()
{
}

void Mob2::Init()
{
	m_attack = IMAGE.GetImage("MOB2_A");
	m_walk = IMAGE.GetImage("MOB2_W");
	m_death = IMAGE.GetImage("MOB2_D");

	m_damage = 15;

	SetTexture(m_walk);
	SetFrameAsRotation(0, m_frameChangeSpeed);
	SetTag("ENEMY");

	SetSpeed(160.0f);
	SetHpModule(200);
	SetRenderLayer(1);

	UseCollider(100, 100);
	UseCenter(texture);
	UseHpBar("HPBAR", 0, -75);

	COL_PX.GetMapViewer()->RegisterEnemy(this);

	SetAutoManaged(false);

	m_gun = Instantiate(Pistol(this, position));
	m_gun->SetBulletTexture("ENEMY_BULLET2", "ENEMY_RING");
	m_gun->SetBulletSpeed(300);

	m_attackRange = 350;
}

void Mob2::Update()
{
	Enemy::Update();
}

void Mob2::Render()
{
	Enemy::Render();
}

void Mob2::Destroy()
{
	Enemy::Destroy();
}

void Mob2::OnCollision(Collider * col)
{
	PushOtherEnemy(col);
}

void Mob2::AttackUpdate()
{
	if (m_frame.nowFrame == m_frame.endFrame) {

		Vector3 movePosit = m_target->position - position;
		D3DXVec3Normalize(&movePosit, &movePosit);

		m_rotation = GetRotation(movePosit);

		SetFrameAsRotation(m_rotation, m_frameChangeSpeed);

		if (m_target)
		{
			if (shotDelay <= GetNowTime()) {
				Instantiate(DownBullet(m_target->position, 800, 500, m_damage));
				shotDelay = GetNowTime() + 1000;
			}
		}
	}
}
