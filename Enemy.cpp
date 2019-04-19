#include "DXUT.h"
#include "Enemy.h"

#include "Pistol.h"
#include "LaserGun.h"
#include "Bazooka.h"

#include "MapViewer.h"
#include "Texture.h"

#include "DamageFont.h"


void Enemy::Init()
{
	SetTexture("ENEMY");
	SetTag("ENEMY");

	SetSpeed(160.0f);
	SetHpModule(100);
	SetRenderLayer(1);

	UseCollider(50, 50);
	UseCenter(texture);

	state = WALK;

	COL_PX.GetMapViewer()->RegisterEnemy(this);
}

void Enemy::Update()
{
	m_frame.OnFrame();

	if (state != DEATH) {

		Vector3 curVec(0, 0, 0);
		float length = 0;

		if (m_target)
		{
			curVec = m_target->position - position;
			length = D3DXVec3Length(&curVec);
		}
		if (length <= m_attackRange)
		{
			if (state != ATTACK)
			{
				state = ATTACK;
				SetTexture(m_attack);

				m_frameChangeSpeed = 250.0f;
			}
		}
		else if (state != WALK)
		{
			state = WALK;
			SetTexture(m_walk);
		}
	}

	if (state != DEATH && curHp <= 0)
	{
		SAFE_DELETE(m_collider);
		COL_PX.GetMapViewer()->UnRegisterEnemy(this);

		m_frameChangeSpeed = 200.0f;

		SetFrameAsRotation(rotation, m_frameChangeSpeed);
		UseFrame(m_frame.startFrame, m_frame.endFrame, m_frameChangeSpeed);

		SetTexture(m_death);

		state = DEATH;
	}

	//CONSOLE_LOG("state : " << state << " frame :" << m_frame.nowFrame);

	switch (state)
	{
	case WALK:
		return WalkUpdate();
		
	case ATTACK:
		return AttackUpdate();

	case DEATH:
		return DeathUpdate();
	}

}

void Enemy::Render()
{
	Vector3 r_scale(scale.x * renderFlip, scale.y, scale.z);

	IMAGE.Render(m_texture->GetImage(m_frame.nowFrame),
		position, r_scale, 0, color);
}

void Enemy::Destroy()
{
	SAFE_DELETE(m_collider);
}

void Enemy::OnCollision(Collider * col)
{
}

void Enemy::OnDamage(int damage)
{
	curHp -= damage;

	Instantiate(DamageFont(damage, position));
}

void Enemy::PushOtherEnemy(Collider * col)
{
	if (col->gameObject->tag == "ENEMY")
	{
		Vector3 ref = col->gameObject->position - position;
		D3DXVec3Normalize(&ref, &ref);
		Vector3 end = col->gameObject->position + ref * GetDeltaTime() * 300;

		if (!COL_PX.PXGetCollisionFlag(&end))
		{
			col->gameObject->position = end;
		}
	}

	if (col->gameObject->tag == "PLAYER")
	{
		Vector3 ref = col->gameObject->position - position;
		D3DXVec3Normalize(&ref, &ref);
		Vector3 end = col->gameObject->position + ref * GetDeltaTime() * 300;

		if (!COL_PX.PXGetCollisionFlag(&end))
		{
			col->gameObject->position = end;
		}

		m_isOnPlayer = true;
	}
	else m_isOnPlayer = false;
}

void Enemy::WalkUpdate()
{
	m_frameChangeSpeed = 50.0f;

	// 적이 있으면
	if (m_target)
	{
		// 방향 구해서
		Vector3 movePosit = m_target->position - position;
		D3DXVec3Normalize(&movePosit, &movePosit);

		// 캐릭터 돌리고
		m_rotation = GetRotation(movePosit);

		// 이동속도 곱한뒤에
		movePosit *= moveSpeed * GetDeltaTime();

		// 충돌 체크
		if (COL_PX.PXGetCollisionFlag(&(m_position + movePosit)))
		{
			// 만약 가려는 곳이 벽이면 
			Vector3 movePosit2(1,0,0);
		
			movePosit2 *= moveSpeed * GetDeltaTime();

			COL_PX.PXGetReflection(&m_position, movePosit2);
		}
		else
		{
			m_position += movePosit;
		}
	}

	SetFrameAsRotation(rotation, m_frameChangeSpeed);
}

void Enemy::DeathUpdate()
{
	if (m_frame.nowFrame == m_frame.endFrame)
	{
		DelHpBar();
		if (m_gun)
			Kill(m_gun);
		Kill();
		DATA.AddGold(INPUT.GetRandom(0, 2));
	}
}

void Enemy::AttackUpdate()
{
	m_frameChangeSpeed = 100;

	if (m_frame.nowFrame == m_frame.endFrame) {

		Vector3 movePosit = m_target->position - position;
		D3DXVec3Normalize(&movePosit, &movePosit);

		m_rotation = GetRotation(movePosit);

		SetFrameAsRotation(m_rotation, m_frameChangeSpeed);

		if (m_target)
		{
			//reinterpret_cast<LifeUnit*>(m_target)->OnDamage(m_damage);

			if (m_gun)
				m_gun->Fire(m_target->position, AUTO_SHOT);
		}

	}
}
