#include "DXUT.h"
#include "InfoRenderer.h"

#include "Player.h"
#include "Gun.h"

#include "GageBar2.h"
#include "Texture.h"

InfoRenderer::InfoRenderer(Player * player)
	: GameObject(OBJKIND::OBJ_UI), m_player(player)
{
	SetRenderType(SCREEN);
	position = Vector3(219, 643, 0);

	SetAutoManaged(false);
}

InfoRenderer::~InfoRenderer()
{
}

void InfoRenderer::Init()
{
	bulletGage = Instantiate(GageBar2("LARGE_BULLETBAR", Vector3(277, 613, 0), 0, 0));
	hpGage = Instantiate(GageBar2("LARGE_HPBAR", Vector3(277, 682, 0), 0, 0));

	bulletGage->SetRenderType(SCREEN);
	bulletGage->SetRenderLayer(4);
	hpGage->SetRenderType(SCREEN);
	hpGage->SetRenderLayer(4);

	SetTexture("LARGE_PANEL");

	gunTexture = nullptr;
	m_prevGun = nullptr;
	m_gun = nullptr;

	SetRenderLayer(3);

	goldTexture = Instantiate(GameObject(OBJKIND::OBJ_UI));
	goldTexture->position = Vector3(102, 58, 0);
	goldTexture->SetTexture("GOLD_PANEL");
	goldTexture->UseCenter(goldTexture->texture);

	goldTexture->renderLayer = 2;
	goldTexture->SetRenderType(SCREEN);

}

void InfoRenderer::Update()
{
	m_gun = m_player->GetGun();

	if (m_player && m_gun) {
		bulletGage->Setting(m_gun->GetMaxBullet(), m_gun->GetCurBullet());
		hpGage->Setting(m_player->GetMaxHp(), m_player->GetCurHp());
	}

	ChangeGunTexture();
	m_prevGun = m_gun;
}

void InfoRenderer::Render()
{
	IMAGE.Render(texture->GetImage(0), position, Vector3(1, 1, 1));

	IMAGE.PrintCenterText(to_string((INT)DATA.GetGold()), Vector3(115, 50, 0), 30);
}

void InfoRenderer::Destroy()
{

}

void InfoRenderer::ChangeGunTexture()
{
	if (m_prevGun != m_gun)
	{
		SAFE_KILL(gunTexture);
		gunTexture = Instantiate(GameObject(OBJ_BACKGROUND));

		gunTexture->SetTexture(m_gun->tag + "_UI", -1);
		gunTexture->UseCenter(gunTexture->texture);

		gunTexture->position = Vector3(85, 645, 0);
		gunTexture->renderLayer = 4;
		gunTexture->SetRenderType(SCREEN);
	}
}
