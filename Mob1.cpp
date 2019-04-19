#include "DXUT.h"
#include "Mob1.h"

#include "Pistol.h"
#include "MapViewer.h"

Mob1::~Mob1()
{
}

void Mob1::Init()
{
	m_attack = IMAGE.GetImage("MOB1_A");
	m_walk	 = IMAGE.GetImage("MOB1_W");
	m_death  = IMAGE.GetImage("MOB1_D");

	m_damage = 5;

	SetTexture(m_walk);
	SetFrameAsRotation(0, m_frameChangeSpeed);
	SetTag("ENEMY");

	SetSpeed(160.0f);
	SetHpModule(150);
	SetRenderLayer(1);

	UseCollider(50, 50);
	UseCenter(texture);
	UseHpBar("HPBAR", 0, -75);

	COL_PX.GetMapViewer()->RegisterEnemy(this);

	m_gun = Instantiate(Pistol(this, position));
	m_gun->SetBulletTexture("ENEMY_BULLET", "ENEMY_RING");
	m_gun->SetBulletSpeed(500);
	m_gun->SetDamage(10);

	SetAutoManaged(false);

	m_attackRange = 350;
}

void Mob1::Update()
{
	Enemy::Update();
}

void Mob1::Render()
{
	Enemy::Render();
}

void Mob1::Destroy()
{
	Enemy::Destroy();
}

void Mob1::OnCollision(Collider * col)
{
	PushOtherEnemy(col);
}