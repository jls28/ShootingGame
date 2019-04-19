#include "DXUT.h"
#include "ScreenEffect.h"

int ScreenEffect::screenEftCount = 0;


ScreenEffect::ScreenEffect(Texture * tex)
	: GameObject(OBJ_EFFECT)
{
	SetTexture(tex);
}

ScreenEffect::~ScreenEffect()
{
}

void ScreenEffect::Init()
{
	SetRenderType(SCREEN);

	SetRenderLayer(10);
	SetPosition(V3CENTER);
	UseCenter(texture);

	alpha = 100;

	SetColor(D3DCOLOR_ARGB(120, 255, 255, 255));
	downMode = false;
	screenEftCount++;
}

void ScreenEffect::Update()
{
	if (alpha <= 248 && downMode == false)
	{
		Lerp(&alpha, alpha, (LONG)350, GetDeltaTime());
		if (alpha >= 248) downMode = true;
	}
	else
	{
		downMode = true;
		Lerp(&alpha, alpha, (LONG)0, GetDeltaTime());
	}

	SetColor(D3DCOLOR_ARGB(alpha, 255, 255, 255));

	if (alpha <= 80)
		Kill();
}

void ScreenEffect::Render()
{
}

void ScreenEffect::Destroy()
{
	screenEftCount--;
}
