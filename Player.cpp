#include "DXUT.h"
#include "Player.h"

#include "Pistol.h"
#include "LaserGun.h"
#include "Bazooka.h"
#include "Spread.h"

#include "MapViewer.h"
#include "InfoRenderer.h"
#include "Texture.h"

#include "Trigger.h"
#include "Mob1.h"

#include "SpawnEffect.h"
#include "ExtinctEffect.h"
#include "FrameEffect.h"
#include "ScreenEffect.h"

#include "Button.h"

void Player::Init()
{
	TextureSet(); // 텍스쳐 불러오기
	WeaponSet(); // 무기에 대한 정보 설정
	SetFrameAsRotation(rotation, m_frameChangeSpeed);

	// 카메라 시선 고정
	CAMERA.SetTarget(this);
	CAMERA.SetPosition(position);

	// 태그 설정
	SetTag("PLAYER");

	// 속도, 체력 설정
	SetSpeed(250.0f);
	SetHpModule(200.0f);
	SetRenderLayer(1);

	// 충돌 범위 설정
	UseCollider(20, 20);
	UseCenter(m_idle[0]);

	// 체력바 사용, 정보 출력 사용, 자동 관리 미사용
	UseHpBar("HPBAR", 0, -75);
	UseInfoRenderer();
	SetAutoManaged(false);
	m_footstepDelay.SetFrame(0, 10, 500);
	m_dashEftDelay.SetFrame(0, 1, 200);

	// 기본 총 : 권총
	m_gunType = NORMAL;
	// 기본 상태 : 걷기
	ChangeState(WALK);
	m_isDeath = false;

	m_gun = nullptr;
	UseOtherGun(NORMAL);

	//m_gun = nullptr;
	m_acceleration = V3ZERO;
	m_canAttack = true;

	COL_PX.GetMapViewer()->RegisterPlayer(this);
}

void Player::Update()
{
	UpdateState();

	m_frame.OnFrame();
	SetFrameAsRotation(rotation, m_frameChangeSpeed);

	CheatKey(); // 주석 처리하면 치트키 사용 불가

	if (curHp <= 0) {
		ChangeState(DEATH);
	}

	switch (m_state)
	{
	case IDLE:	 IdleUpdate();	 break;
	case WALK:	 WalkUpdate();	 break;
	case ATTACK: AttackUpdate(); break;
	case DEATH:	 DeathUpdate();  break;
	}
}

void Player::Render()
{
	IMAGE.Render(m_texture->GetImage(m_frame.nowFrame), position, scale, 0);
}

void Player::Destroy()
{
	CAMERA.SetTarget(nullptr);
	SAFE_DELETE(m_collider);
	DelInfoRenderer();
	DelHpBar();
}

void Player::OnCollision(Collider * col)
{
}

void Player::OnDamage(int damage)
{
	curHp -= damage;

	if (curHp <= 0)
		curHp = 0;

	if (ScreenEffect::screenEftCount < 2) {
		if (curHp <= maxHp * 0.2)
			Instantiate(ScreenEffect(IMAGE.GetImage("SCREEN_EFT3")));
		else
			Instantiate(ScreenEffect(IMAGE.GetImage("SCREEN_EFT2")));
	}
}

void Player::UpdateState()
{
	if (m_state == DEATH) return;
	if (m_isDeath) return;

	Vector3 movePosit = INPUT.GetAxisDirection();

	movePosit *= moveSpeed * GetDeltaTime();

	COL_PX.PXGetReflection(&m_position, movePosit);

	if (INPUT.GetKeyPress(VK_LBUTTON) && !m_gun->IsReload() && m_canAttack)
		ChangeState(ATTACK);
	else if (m_state == ATTACK && (m_frame.nowFrame != m_frame.endFrame))
		return;
	else if (movePosit != V3ZERO)
		ChangeState(WALK);
	else
		ChangeState(IDLE);

	if (m_footstepDelay.OnFrame() && movePosit != V3ZERO)
		SOUND.DuplicatePlay("FOOT_STEP", 90);
}


// 아이들(기본) 상태 업데이트
void Player::IdleUpdate()
{
	SetFrameChangeSpeed(50);

	Vector3 movePosit = INPUT.GetAxisDirection();

	if (movePosit != V3ZERO)
		rotation = GetRotation(movePosit);
}

// 공격 상태 업데이트
void Player::AttackUpdate()
{
	SetSpeed(250.0f); m_footstepDelay.delay = 500;

	SetFrameChangeSpeed((float)m_weaponAttackSpeed[m_gunType] / 10);

	Vector3 dir = INPUT.GetScrollMouse() - position;
	D3DXVec3Normalize(&dir, &dir);

	rotation = GetRotation(dir);

	if (m_frame.nowFrame % 10 == m_weaponAttackTime[m_gunType]) {

		if (m_gun)
			m_gun->Fire(INPUT.GetScrollMouse(), AUTO_SHOT);
	}
}

// 걷기 상태 업데이트
void Player::WalkUpdate()
{
	Vector3 movePosit = INPUT.GetAxisDirection();

	if (movePosit != V3ZERO)
		rotation = GetRotation(movePosit);

	if (INPUT.GetKeyPress(VK_LSHIFT))
	{
		SetSpeed(450.0f);
		SetFrameChangeSpeed(25);
		m_footstepDelay.delay = 200;

		if (m_dashEftDelay.OnFrame())
		{
			float rot = m_rotation - 180;

			Vector3 sPos(cosf(D3DXToRadian(rot)) * 50 + position.x,
				sinf(D3DXToRadian(rot)) * 50 + position.y, 0);

			Instantiate(ExtinctEffect("DASH_EFT", sPos +
				Vector3(INPUT.GetRandom(-30, 30), 50, 0), 0))->SetRenderLayer(m_renderLayer - 1);
		}
	}
	else
	{
		SetSpeed(250.0f);
		SetFrameChangeSpeed(50);
		m_footstepDelay.delay = 350;
	}
}

// 사망 상태 업데이트
void Player::DeathUpdate()
{
	m_frame.delay = 200.0f;

	if (!m_isDeath && (m_frame.nowFrame == m_frame.endFrame)) {

		m_isDeath = true;

		SOUND.Stop("BGM");
		SOUND.Stop("BOSS_BGM");
		SOUND.Play("LOSE", 1);

		SetRenderMode(RENDERMODE_NONE);

		COL_PX.GetMapViewer()->UnRegisterPlayer();

		SAFE_DELETE(m_collider);

		auto gameover = Instantiate(GameObject(OBJKIND::OBJ_UI));
		gameover->position = V3CENTER;
		gameover->SetTexture("GAMEOVER");
		gameover->UseCenter(gameover->texture);

		gameover->renderLayer = 15;
		gameover->SetRenderType(SCREEN);

		auto btn1 = Instantiate(Button(Vector3(WINSIZEX/2 - 120, WINSIZEY / 2 + 200, 0), "RE_BUTTON", 200, 100, [&]() {
			SCENE.ChangeScene("S_STAGE1");
		}));
		btn1->SetRenderLayer(16);
		btn1->SetRenderType(SCREEN);

		auto btn2 = Instantiate(Button(Vector3(WINSIZEX/2 + 120, WINSIZEY / 2 + 200, 0), "MAIN_BUTTON", 200, 100, [&]() {
			SCENE.ChangeScene("S_TITLE");
		}));
		btn2->SetRenderLayer(16);
		btn2->SetRenderType(SCREEN);
	}
}

// 상태 전환
void Player::ChangeState(int state)
{
	if (state == m_state)
		return;

	m_state = state;

	switch (state)
	{
	case IDLE:	 SetTexture(m_idle[m_gunType]);	  break;
	case WALK:	 SetTexture(m_walk[m_gunType]);	m_footstepDelay.SetFrame(0, 10, 50);  break;
	case ATTACK: SetTexture(m_attack[m_gunType]); break;
	case DEATH:	 SetTexture(m_death);			  break;
	}
}

// 총 전환
void Player::ChangeGun(int gunType)
{
	m_gunType = gunType;

	switch (m_state)
	{
	case IDLE:	 SetTexture(m_idle[m_gunType]);	  break;
	case WALK:	 SetTexture(m_walk[m_gunType]);	  break;
	case ATTACK: SetTexture(m_attack[m_gunType]); break;
	case DEATH:	 SetTexture(m_death);			  break;
	}
}

// 텍스쳐 불러오기
void Player::TextureSet()
{
	m_normalAttack = IMAGE.GetImage("PLAYER_A_NORMAL");
	m_laserAttack = IMAGE.GetImage("PLAYER_A_LASER");
	m_bazookaAttack = IMAGE.GetImage("PLAYER_A_BAZOOKA");
	m_spreadAttack = IMAGE.GetImage("PLAYER_A_SPREAD");

	m_normalIdle = IMAGE.GetImage("PLAYER_I_NORMAL");
	m_laserIdle = IMAGE.GetImage("PLAYER_I_LASER");
	m_bazookaIdle = IMAGE.GetImage("PLAYER_I_BAZOOKA");
	m_spreadIdle = IMAGE.GetImage("PLAYER_I_SPREAD");

	m_normalWalk = IMAGE.GetImage("PLAYER_W_NORMAL");
	m_laserWalk = IMAGE.GetImage("PLAYER_W_LASER");
	m_bazookaWalk = IMAGE.GetImage("PLAYER_W_BAZOOKA");
	m_spreadWalk = IMAGE.GetImage("PLAYER_W_SPREAD");

	m_death = IMAGE.GetImage("PLAYER_D");
}

// 총 정보 설정
void Player::WeaponSet()
{
	m_weaponAttackSpeed[NORMAL] = 175;
	m_weaponAttackSpeed[LASER] = 1000;
	m_weaponAttackSpeed[BAZOOKA] = 850;
	m_weaponAttackSpeed[SPREAD] = 500;

	m_weaponAttackTime[NORMAL] = 1;
	m_weaponAttackTime[LASER] = 3;
	m_weaponAttackTime[BAZOOKA] = 4;
	m_weaponAttackTime[SPREAD] = 4;
}

// 프레임 간격 조정
void Player::SetFrameChangeSpeed(float speed)
{
	m_frameChangeSpeed = speed;

	m_frame.delay = speed;
}

// 인포 렌더러 사용
void Player::UseInfoRenderer()
{
	if (!m_infoRenderer)
		m_infoRenderer = Instantiate(InfoRenderer(this));
}

// 인포 렌더러 삭제
void Player::DelInfoRenderer()
{
	SAFE_KILL(m_infoRenderer);
}

// 치트키 모음 함수
void Player::CheatKey()
{
	if (INPUT.GetKeyDown(VK_F1))
		SCENE.ChangeScene("S_STAGE1");
	if (INPUT.GetKeyDown(VK_F2))
		SCENE.ChangeScene("S_STAGE2");

	if (INPUT.GetKeyDown('1'))
		UseOtherGun(NORMAL);
	
	if (INPUT.GetKeyDown('2'))
		UseOtherGun(LASER);

	if (INPUT.GetKeyDown('3'))
		UseOtherGun(BAZOOKA);

	if (INPUT.GetKeyDown('4'))
		UseOtherGun(SPREAD);
}

void Player::UseOtherGun(int gunType)
{
	switch (gunType) {
	case NORMAL:
		SAFE_KILL(m_gun);
		m_gun = Instantiate(Pistol(this, position));
		m_gun->SetBulletTexture("NORMAL_BULLET", "RING_EFT");
		ChangeGun(NORMAL);
		break;
	case LASER:
		SAFE_KILL(m_gun);
		m_gun = Instantiate(LaserGun(this, position));
		ChangeGun(LASER);
		break;
	case BAZOOKA:
		SAFE_KILL(m_gun);
		m_gun = Instantiate(Bazooka(this, position));
		m_gun->SetBulletTexture("BAZOOKA_BULLET", "BAZOOKA_EFT");
		ChangeGun(BAZOOKA);
		break;
	case SPREAD:
		SAFE_KILL(m_gun);
		m_gun = Instantiate(Spread(this, position));
		m_gun->SetBulletTexture("SPREAD_BULLET", "SPREAD_EFT");
		ChangeGun(SPREAD);
		break;
	}
};