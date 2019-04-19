#pragma once
#include "GameObject.h"

class Player;
class Gun;

class GageBar2;
class InfoRenderer :
	public GameObject
{
private:
	Player * m_player;
	Gun* m_prevGun;
	Gun* m_gun;

	GageBar2* bulletGage;
	GageBar2* hpGage;

	GameObject* gunTexture;
	GameObject* goldTexture;

public:
	InfoRenderer(Player* player);
	~InfoRenderer();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void ChangeGunTexture();
};

