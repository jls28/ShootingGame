#include "DXUT.h"
#include "BossWarning.h"

#include "Texture.h"

BossWarning::BossWarning()
	: GameObject(OBJ_UI)
{
}


BossWarning::~BossWarning()
{
}

void BossWarning::Init()
{
	onoff = IMAGE.GetImage("BOSS_ONOFF");
	bossWarnings = IMAGE.GetImage("BOSS_WARNING");

	poses[0] = Vector3(WINSIZEX / 2, -WINSIZEY / 2, 0);
	poses[1] = Vector3(WINSIZEX, WINSIZEY, 0);
	poses[2] = Vector3(WINSIZEX, WINSIZEY / 2, 0);
	poses[2] = Vector3(WINSIZEX * 2, WINSIZEY / 2, 0);

	destTime = GetNowTime() + 2000;

	SetRenderLayer(10);
	SetRenderType(SCREEN);
}

void BossWarning::Update()
{
	Lerp(&poses[0], poses[0], V3CENTER, GetDeltaTime() * 3);
	Lerp(&poses[1], poses[1], V3CENTER, GetDeltaTime() * 3);
	Lerp(&poses[2], poses[2], V3CENTER, GetDeltaTime() * 3);
	Lerp(&poses[3], poses[3], V3CENTER, GetDeltaTime() * 1);

	if (destTime <= GetNowTime())
		Kill();
}

void BossWarning::Render()
{
	IMAGE.Render(bossWarnings->GetImage(0), poses[0], Vector3(1, 1, 1));
	IMAGE.Render(bossWarnings->GetImage(1), poses[1], Vector3(1, 1, 1));
	IMAGE.Render(bossWarnings->GetImage(2), poses[2], Vector3(1, 1, 1));
	IMAGE.Render(bossWarnings->GetImage(3), poses[3], Vector3(1, 1, 1));

	IMAGE.Render(onoff, V3CENTER, Vector3(1, 1, 1));
}

void BossWarning::Destroy()
{

}
