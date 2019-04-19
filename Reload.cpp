#include "DXUT.h"
#include "Reload.h"
#include "Texture.h"

Reload::Reload(GameObject * target, Vector3 offset, float lifeTime)
	: GameObject(OBJKIND::OBJ_UI), target(target), offset(offset)
{
	m_position = target->position + offset;

	startTime = GetNowTime();
	endTime = startTime + lifeTime;

	SetRenderLayer(3);

	SetAutoManaged(false);
	reloadText = IMAGE.GetImage("RELOAD_T");
}

Reload::~Reload()
{
}

void Reload::Init()
{
	SetTexture("RELOAD");
	width = texture->GetImage(0)->info.Width;
}

void Reload::Update()
{
	if (GetNowTime() >= endTime)
	{
		Kill();

		return;
	}

	float nowT = GetNowTime();
	float perc = (float)(endTime - nowT) / (float)(endTime - startTime);

	barX = width * abs(1.0f - perc) + position.x - width / 2;

	position = target->position + offset;
}

void Reload::Render()
{
	IMAGE.Render(texture->GetImage(0), position, scale);
	IMAGE.Render(texture->GetImage(1), Vector3(barX, position.y, 0), scale);
	IMAGE.Render(reloadText, position + Vector3(0, -20, 0), scale);
}

void Reload::Destroy()
{
}
