#pragma once
#include "GameObject.h"

enum UNIT_STATE
{
	WALK,
	DEATH,
	ATTACK,
	RUSH
};

class GageBar;
class LifeUnit :
	public GameObject
{
protected:
	int curHp = 0;
	int maxHp = 0;

	int state = WALK;

	float moveSpeed = 0;

	GageBar* gageBar = nullptr;
public:
	LifeUnit(INT objKind) : GameObject((OBJKIND)objKind) {}
	virtual ~LifeUnit() {}

	virtual void OnDamage(int damage) { curHp -= damage; }

	void SetHpModule(int hp) { curHp = maxHp = hp; }
	void SetSpeed(float speed) { moveSpeed = speed; }

	void UseHpBar(const string& hpbarName, float offsetX, float offsetY);
	void DelHpBar();

	int GetMaxHp() {
		return maxHp;
	}
	int GetCurHp() {
		return curHp;
	}

	void Heal(int heal) { curHp += heal; if (maxHp < curHp) curHp = maxHp; }

	void SetFrameAsRotation(float rot, float frameChangeSpeed);
};

