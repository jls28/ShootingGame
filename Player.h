#pragma once
#include "LifeUnit.h"

enum GUN_TYPE {
	NORMAL,
	LASER,
	BAZOOKA,
	SPREAD
};

class Gun;
class InfoRenderer;

class Player :
	public LifeUnit
{
private:
	Gun * m_gun = nullptr;

	Vector3 m_acceleration;

	InfoRenderer* m_infoRenderer = nullptr;

	INT m_gunType = 0;
	INT m_state = 0;
	INT m_frameChangeSpeed = 0;

	INT m_weaponAttackSpeed[4];
	INT m_weaponAttackTime[4];

	Frame m_footstepDelay;
	Frame m_dashEftDelay;

	BOOL m_canAttack;

	BOOL m_isDeath;

public:
	Player() : LifeUnit(OBJKIND::OBJ_PLAYER) { position = V3ZERO; }
	Player(Vector3 position) : LifeUnit(OBJKIND::OBJ_PLAYER) { GameObject::position = position; }
	Player(float x, float y, float z) : Player(Vector3(x, y, z)) {}
	virtual ~Player() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	virtual void OnDamage(int damage) override;

	void UpdateState();

	Gun* GetGun() { return m_gun; }

	void UseInfoRenderer();
	void DelInfoRenderer();

	void IdleUpdate();
	void AttackUpdate();
	void WalkUpdate();
	void DeathUpdate();

	void ChangeState(int state);
	void ChangeGun(int gunType);

	void TextureSet();
	void WeaponSet();

	void SetFrameChangeSpeed(float speed);
	void CheatKey();

	void UseOtherGun(int gunType);

	void SetCanAttack(bool can) { m_canAttack = can; }
	bool GetCanAttack() { return m_canAttack; }

private:
#pragma region TEXTURES

	enum PLAYER_STATE
	{
		IDLE,
		WALK,
		ATTACK,
		DEATH
	};

	union {
		struct
		{
			Texture* m_normalAttack;
			Texture* m_laserAttack;
			Texture* m_bazookaAttack;
			Texture* m_spreadAttack;
		};
		Texture* m_attack[4];
	};

	union {
		struct
		{
			Texture* m_normalIdle;
			Texture* m_laserIdle;
			Texture* m_bazookaIdle;
			Texture* m_spreadIdle;
		};
		Texture* m_idle[4];
	};

	union {
		struct {
			Texture* m_normalWalk;
			Texture* m_laserWalk;
			Texture* m_bazookaWalk;
			Texture* m_spreadWalk;
		};
		Texture* m_walk[4];
	};

	Texture* m_death = nullptr;

#pragma endregion
};

