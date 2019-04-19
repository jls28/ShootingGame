#include "DXUT.h"
#include "Boss.h"

#include "DamageFont.h"
#include "MapViewer.h"

#include "Pistol.h"
#include "LaserGun.h"
#include "DownBullet.h"

#include "BossWarning.h"
#include "Button.h"

#define RUSH_RED 3

Boss::Boss(float x, float y, GameObject* target)
	: Enemy(x, y, 0, target)
{

}

Boss::~Boss()
{
}

void Boss::Init()
{
	m_attack = IMAGE.GetImage("BOSS_A");
	m_walk = IMAGE.GetImage("BOSS_W");
	m_death = IMAGE.GetImage("BOSS_D");
	m_rush = IMAGE.GetImage("BOSS_R");

	m_damage = 30;

	SetTexture(m_walk);
	SetFrameAsRotation(0, m_frameChangeSpeed);
	SetTag("ENEMY");

	SetSpeed(160.0f);
	SetHpModule(2000);
	SetRenderLayer(1);

	UseCollider(100, 100);
	UseCenter(texture);
	UseHpBar("HPBAR", 0, -75);

	COL_PX.GetMapViewer()->RegisterBoss(this);

	SetAutoManaged(false);

	m_rushRange = 1000;
	m_attackRange = 500;

	CAMERA.SetTarget(this);

	m_cameraTime = GetNowTime() + 2000;

	SOUND.Stop("BGM");
	SOUND.Play("BOSS_BGM", 1);

	SOUND.DuplicatePlay("WARNING", 100);

	Instantiate(BossWarning);

	m_gun = Instantiate(Pistol(this, position));
	m_gun->SetBulletTexture("BOSS_BULLET1", "BOSS_BULLET_EFT1");
	m_gun->SetBulletSpeed(500);

	m_gun2 = Instantiate(LaserGun(this, position));
	m_gun2->SetBulletSpeed(500);

	m_nowGunMode = false;
}

void Boss::Update()
{
	m_frame.OnFrame();

	if (m_cameraTime != 0)
	{
		FocusUpdate();
		return;
	}

	if (state != DEATH) {

		Vector3 curVec(0, 0, 0);
		float length = 10000;

		if (m_target)
		{
			curVec = m_target->position - position;
			length = D3DXVec3Length(&curVec);
		}

		if (state == RUSH || (length <= m_rushRange && length > m_attackRange))
		{
			if (state != RUSH)
			{
				state = RUSH;
				SetTexture(m_rush);
			}
			else if (m_frame.nowFrame == m_frame.endFrame)
			{
				state = ATTACK;
				SetTexture(m_attack);
			}
		}
		else if (length <= m_attackRange)
		{
			if (state != ATTACK)
			{
				state = ATTACK;

				SetTexture(m_attack);
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
		COL_PX.GetMapViewer()->UnRegisterBoss();

		m_frameChangeSpeed = 200.0f;

		SetFrameAsRotation(rotation, m_frameChangeSpeed);
		UseFrame(m_frame.startFrame, m_frame.endFrame, m_frameChangeSpeed);

		SetTexture(m_death);

		state = DEATH;
	}

	switch (state)
	{
	case WALK:
		return WalkUpdate();

	case ATTACK:
		return AttackUpdate();

	case RUSH:
		return RushUpdate();

	case DEATH:
		return DeathUpdate();
	}
}

void Boss::Render()
{
	Enemy::Render();
}

void Boss::Destroy()
{
	Enemy::Destroy();
}

void Boss::OnCollision(Collider * col)
{
	PushOtherEnemy(col);
}

void Boss::OnDamage(int damage)
{
	curHp -= damage;

	Instantiate(DamageFont(damage, position));
}

void Boss::AttackUpdate()
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

			if (m_nowGunMode) {
				if (m_gun)
					m_gun->Fire(m_target->position, AUTO_SHOT);
			}
			else
			{
				if (m_shotDelay <= GetNowTime()) {
					Instantiate(DownBullet(m_target->position, 800, 500, m_damage));
					m_shotDelay = GetNowTime() + 1000;
				}
			}
			m_nowGunMode = !m_nowGunMode;
		}
	}
}

void Boss::DeathUpdate()
{
	if (m_frame.nowFrame == m_frame.endFrame)
	{
		DelHpBar();
		if (m_gun)
			Kill(m_gun);
		Kill();

		SOUND.Stop("BGM");
		SOUND.Stop("BOSS_BGM");
		SOUND.Play("WIN", 1);

		SetRenderMode(RENDERMODE_NONE);

		auto gameover = Instantiate(GameObject(OBJKIND::OBJ_UI));
		gameover->position = V3CENTER;
		gameover->SetTexture("CLEAR");
		gameover->UseCenter(gameover->texture);

		gameover->renderLayer = 15;
		gameover->SetRenderType(SCREEN);

		auto btn1 = Instantiate(Button(Vector3(WINSIZEX / 2 - 120, WINSIZEY / 2 + 200, 0), "RE_BUTTON", 200, 100, [&]() {
			SCENE.ChangeScene("S_STAGE1");
			}));
		btn1->SetRenderLayer(16);
		btn1->SetRenderType(SCREEN);

		auto btn2 = Instantiate(Button(Vector3(WINSIZEX / 2 + 120, WINSIZEY / 2 + 200, 0), "MAIN_BUTTON", 200, 100, [&]() {
			SCENE.ChangeScene("S_TITLE");
			}));
		btn2->SetRenderLayer(16);
		btn2->SetRenderType(SCREEN);
	}
}


void Boss::FocusUpdate()
{
	if (m_cameraTime <= GetNowTime()) {

		SOUND.DuplicatePlay("WARNING", 100);
	
		CAMERA.SetTarget(m_target);
		m_cameraTime = 0;
	}
}

void Boss::RushUpdate()
{
	m_frameChangeSpeed = 125.0f;

	// 적이 있으면
	if (m_target)
	{
		// 방향 구해서
		Vector3 movePosit = m_target->position - position;

		if (m_frame.nowFrame == m_frame.endFrame && 50 <= D3DXVec3Length(&movePosit))
		{
			reinterpret_cast<LifeUnit*>(m_target)->OnDamage(25);
		}

		D3DXVec3Normalize(&movePosit, &movePosit);

		if (m_frame.nowFrame == m_frame.endFrame) {
			//캐릭터 돌리고
			m_rotation = GetRotation(movePosit);

			SetFrameAsRotation(rotation, m_frameChangeSpeed);
		}

		// 이동속도 x 5 곱한뒤에
		movePosit *= moveSpeed * RUSH_RED * GetDeltaTime();

		// 충돌 체크
		if (COL_PX.PXGetCollisionFlag(&(m_position + movePosit)))
		{
			// 만약 가려는 곳이 벽이면 
			Vector3 movePosit2(1, 0, 0);

			movePosit2 *= moveSpeed * RUSH_RED * GetDeltaTime();

			COL_PX.PXGetReflection(&m_position, movePosit2);
		}
		else
		{
			m_position += movePosit;
		}
	}
}
