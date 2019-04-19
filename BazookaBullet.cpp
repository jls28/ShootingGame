#include "DXUT.h"
#include "BazookaBullet.h"

#include "ExtinctEffect.h"
#include "LifeUnit.h"
#include "Explode.h"

BazookaBullet::BazookaBullet(const string & shooter_tag, Vector3 start, 
	Vector3 dir, float speed, float damage)
	: NormalBullet(shooter_tag, start, dir, speed, damage)
{

}

BazookaBullet::~BazookaBullet()
{
}

void BazookaBullet::Init()
{
	NormalBullet::Init();
}

void BazookaBullet::Update()
{
	if (ringSpawnTime <= GetNowTime())
	{
		rotation = GetRotation(m_direcition);
		Instantiate(ExtinctEffect(eftImg, position, rotation));

		ringSpawnTime = GetNowTime() + ringDelay;
	}

	Vector3 move(0, 0, 0);

	move = m_direcition * m_speed * GetDeltaTime() + position;

	if (!COL_PX.PXGetCollisionFlag(&move))
	{
		position = move;
	}
	else
	{
		Instantiate(Explode(position, m_shooter, 1, m_damage));
		Kill();
	}
}

void BazookaBullet::Render()
{
	NormalBullet::Render();
}

void BazookaBullet::Destroy()
{
}

void BazookaBullet::OnCollision(Collider * col)
{
	if (col->gameObject->tag == "PLAYER" || col->gameObject->tag == "ENEMY")
	{
		LifeUnit* tar = reinterpret_cast<LifeUnit*>(col->gameObject);

		if (tar->tag == m_shooter)
			return;
		else
		{
			Instantiate(Explode(position, m_shooter, 1.3, m_damage));
			Kill();
		}
	}
}
