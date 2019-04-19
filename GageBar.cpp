#include "DXUT.h"
#include "GageBar.h"

#include "Texture.h"

GageBar::GageBar(const string& texture, Vector3 & target, int & max, int & cur, Vector3 offset)
	: GameObject(OBJKIND::OBJ_UI),
	targetPos(target), maxHp(max), curHp(cur), offset(offset)
{
	SetTexture(texture);
	SetRenderLayer(3);

	imgCnt = m_texture->size();

	SetAutoManaged(false);
}

GageBar::~GageBar()
{
}

void GageBar::Init()
{
	TextureInfo info = texture->GetImage(1)->info;

	infoSize = Vector3(info.Width, info.Height, 0);

	contraWidth = infoSize.x;
}

void GageBar::Update()
{
	float perc = (float)curHp / (float)maxHp;

	float prevWidth = width;
	width = infoSize.x * perc;

	Lerp(&contraWidth, contraWidth, width, GetDeltaTime() * 1.5);

	//CONSOLE_LOG(curHp << "/" << maxHp);

	//CONSOLE_LOG(targetPos.x << ", " << targetPos.y);
}

void GageBar::Render()
{
	Vector3 pos = targetPos + offset;
	if (imgCnt == 1) {
		RECT rc = { 0,0, (LONG)width,infoSize.y };
		IMAGE.CropRender(texture->GetImage(0), pos, rc);
	}
	else if (imgCnt == 2) {
		IMAGE.Render(texture->GetImage(0), pos, Vector3(1, 1, 1));
		RECT rc = { 0,0, (LONG)width,infoSize.y };
		IMAGE.CropRender(texture->GetImage(1), pos, rc);
	}
	else if (imgCnt == 3) {
		IMAGE.Render(texture->GetImage(0), pos, Vector3(1, 1, 1));

		RECT rc = { 0,0,contraWidth,infoSize.y };
		IMAGE.CropRender(texture->GetImage(1), pos, rc);

		rc.right = width;
		IMAGE.CropRender(texture->GetImage(2), pos, rc);
	}
}

void GageBar::Destroy()
{
}
