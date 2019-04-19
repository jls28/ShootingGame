#include "DXUT.h"
#include "DamageFont.h"


DamageFont::DamageFont(int damage, Vector3 start)
	: Parabola(OBJKIND::OBJ_UI), m_damage(damage)
{
	Setting(start, start +
		Vector3(INPUT.GetRandom(-60, 60), INPUT.GetRandom(10, 30), 0),
		0.4, INPUT.GetRandom(30, 50));

	if (damage < 10)
	{
		SetColor(D3DCOLOR_ARGB(175, 255, 123, 0)); m_fontSize = 15;
	}
	else if (damage < 50)
	{
		SetColor(D3DCOLOR_ARGB(200, 255, 50, 0)); m_fontSize = 25;
	}
	else
	{
		SetColor(D3DCOLOR_ARGB(255, 255, 0, 0)); m_fontSize = 35;
	}
}

DamageFont::~DamageFont()
{
}

void DamageFont::Init()
{
	SetRenderLayer(4);
}

void DamageFont::Update()
{
	if (IsEnd())
	{
		Kill();
	}
}

void DamageFont::Render()
{
	IMAGE.PrintCenterText("-" + to_string(m_damage), position, 40, color);
}

void DamageFont::Destroy()
{
}
