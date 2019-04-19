#include "DXUT.h"
#include "Bullet.h"

#include "LifeUnit.h"

Bullet::Bullet(const string & shooter_tag, Vector3 start, Vector3 dir, float speed, float damage)
	: GameObject(OBJKIND::OBJ_BULLET), m_shooter(shooter_tag),
		m_direcition(dir), m_speed(speed), m_damage(damage)
{
	position = start;
	SetTag("BULLET");
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	SetTexture("BULLET");

	UseCollider(10);
	UseCenter(texture);
	SetRenderLayer(1);
}

void Bullet::Update()
{
	Vector3 move(0, 0, 0);

	move = m_direcition * m_speed * GetDeltaTime() + position;

	if (!COL_PX.PXGetCollisionFlag(&move))
	{
		position = move;
	}
	else
		Kill();
}

void Bullet::Render()
{
}

void Bullet::Destroy()
{

}

void Bullet::OnCollision(Collider * col)
{
	if (col->gameObject->tag == "PLAYER" || col->gameObject->tag == "ENEMY")
	{
		LifeUnit* tar = reinterpret_cast<LifeUnit*>(col->gameObject);

		if (tar->tag == m_shooter)
			return;
		else
		{
			Kill();
			tar->OnDamage(m_damage);
		}
	}
}
