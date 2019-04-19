#include "DXUT.h"
#include "MapViewer.h"

#include "Texture.h"

#define PIVOT_POS Vector3(center.x, center.y, 0)
#define RED_SCALE  0.25
// ¹Ì´Ï¸Ê À§¿¡ MINIMAP ±ÛÀÚ yÃà ÇÈ¼¿

MapViewer::MapViewer(Texture * mapTexture)
	: GameObject(OBJKIND::OBJ_UI), player(nullptr), boss(nullptr), map(mapTexture)
{
	renderType = SCREEN;
	SetAutoManaged(false);

	SetTexture(IMAGE.AddImage("MINIMAP_VIEWER", "./Resource/ui/minimap.png"));

	playerIcon = IMAGE.AddImage("PLAYER_ICON", "./Resource/ui/playerIcon.png");
	bossIcon = IMAGE.AddImage("BOSS_ICON", "./Resource/ui/bossIcon.png");
	enemyIcon = IMAGE.AddImage("ENEMY_ICON", "./Resource/ui/enemyIcon.png");

	worldMap = IMAGE.AddImage("WORLD_MAP", "./Resource/ui/worldMap.png");
	minimapText = IMAGE.AddImage("MINIMAP_TEXT", "./Resource/ui/minimap_t.png");

	UseCenter(texture);
	SetPosition(WINSIZEX - center.x, WINSIZEY - center.y);

	m_center.x -= 10;
	m_center.y -= 10;
}

MapViewer::~MapViewer()
{
}

void MapViewer::Init()
{
	minimapData = COL_PX.miniMap;
	COL_PX.SetMapViewer(this);

	SetRange();

	range = { 0,0, (LONG)(center.x * 2) , (LONG)((center.y) * 2) };
}

void MapViewer::Update()
{
	SetRange();

	tab = INPUT.GetKeyPress(VK_TAB);
}

void MapViewer::Render()
{
	if (tab)
	{
		IMAGE.Render(worldMap, V3CENTER - Vector3(0, 12, 0), Vector3(1.0, 1.0, 0));
		IMAGE.Render(map, V3CENTER, Vector3(0.13, 0.13, 0), 0, D3DCOLOR_ARGB(180, 255, 255, 255));
	}

	Vector3 renderPivot = position - PIVOT_POS;

	IMAGE.CropCenterRender(minimapData->GetImage(0),
		renderPivot, Vector3(2.5, 2.5, 0),
		Vector3(0, 0, 0), range);

	if (player)
		MiniMapInsideRender(player->position, playerIcon);
	if (boss)
		MiniMapInsideRender(boss->position, bossIcon);

	for (auto iter : enemys)
	{
		MiniMapInsideRender(iter->position, enemyIcon);
	}

	IMAGE.CenterRender(minimapText, position + Vector3(0, -50, 0) - m_center, scale, V3ZERO);
	IMAGE.Render(texture->GetImage(0), position, scale);
}

void MapViewer::Destroy()
{
}

void MapViewer::SetRange()
{
	range.left = (CAMERA.GetPosition() - V3CENTER).x * 0.1;
	range.top = (CAMERA.GetPosition() - V3CENTER).y * 0.1;
	range.right = (CAMERA.GetPosition() - V3CENTER).x * 0.1 + (LONG)((center.x) * 2);
	range.bottom = (CAMERA.GetPosition() - V3CENTER).y * 0.1 + (LONG)((center.y) * 2);
}

void MapViewer::RegisterEnemy(GameObject * enemy)
{
	enemys.push_back(enemy);
}

void MapViewer::RegisterPlayer(GameObject * player)
{
	MapViewer::player = player;
}

void MapViewer::RegisterBoss(GameObject * boss)
{
	MapViewer::boss = boss;
}

void MapViewer::UnRegisterBoss()
{
	MapViewer::boss = nullptr;
}

void MapViewer::UnRegisterEnemy(GameObject * enemy)
{
	enemys.remove(enemy);
}

void MapViewer::UnRegisterPlayer()
{
	MapViewer::player = nullptr;
}

void MapViewer::MiniMapInsideRender(Vector3 position, Texture * tex)
{
	Vector3 r_pos = (position - CAMERA.GetPosition()) * RED_SCALE + MapViewer::position;
	Vector3 p = MapViewer::position - PIVOT_POS + Vector3(10, 10, 0);

	if (r_pos.x > p.x &&
		r_pos.x < WINSIZEX &&
		r_pos.y > p.y &&
		r_pos.y < WINSIZEY)
		IMAGE.Render(tex, r_pos, Vector3(1, 1, 1));
}