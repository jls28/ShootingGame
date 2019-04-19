#include "DXUT.h"
#include "Explode.h"

#include "LifeUnit.h"
#include "Texture.h"

Explode::Explode(Vector3 position, const string & shooter, float size, float damage)
	: GameObject(OBJKIND::OBJ_EFFECT), shooter(shooter), damage(damage)
{
	m_position = position;
	m_scale.x = m_scale.y = m_scale.z = size;
	endAttack = false;

	SetRenderLayer(1);
}

Explode::~Explode()
{
}

void Explode::Init()
{
	SetTexture("EXPLODE");
	UseFrame(0, 5, 100);
	UseCenter(texture->GetImage(1));

	SOUND.DuplicateDistancePlay("EXPLODE", position);
}

void Explode::Update()
{
	if (m_frame.nowFrame == 1)
		UseCollider(220 * m_scale.x);

	if (endAttack)
		SAFE_DELETE(collider);

	if (m_frame.nowFrame == m_frame.endFrame)
	{
		Kill();	
	}
}

void Explode::Render()
{
}

void Explode::Destroy()
{
}

void Explode::OnCollision(Collider * col)
{
	if (col->gameObject->tag != shooter)
	{
		LifeUnit* target = dynamic_cast<LifeUnit*>(col->gameObject);

		if (target)
		{
			target->OnDamage(damage);
			endAttack = true;
		}
	}
}
