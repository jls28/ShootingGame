#include "DXUT.h"
#include "TitleUnits.h"

#include "Texture.h"
#include "Button.h"

#include "FrameEffect.h"

TitleUnits::TitleUnits()
	: GameObject(OBJKIND::OBJ_BACKGROUND)
{
	SetAutoManaged(false);
}


TitleUnits::~TitleUnits()
{
}

void TitleUnits::Init()
{
	peoples = IMAGE.GetImage("PEOPLES");

	peopleMove[0] = Fluffy(Vector3(WINSIZEX/2, 380, 0), 380, 390, 20);
	peopleMove[1] = Fluffy(Vector3(1280, 380, 0), 380, 390, 20);
	peopleMove[2] = Fluffy(Vector3(0, 380, 0), 380, 390, 20);

	cloud = GameObject::CreateBackGround("CLOUD", -1);
	title = nullptr;
	cloudMove = Fluffy(cloud->position, WINSIZEY / 2, WINSIZEY / 2 + 2, 2);

	howto_w = GameObject::CreateBackGround("HOWTO_W", 11);
	howto_w->SetRenderMode(RENDERMODE_NONE); howto_w->SetRenderType(SCREEN);
	info_w = GameObject::CreateBackGround("INFO_W", 11);
	info_w->SetRenderMode(RENDERMODE_NONE); info_w->SetRenderType(SCREEN);
	rank_w = GameObject::CreateBackGround("RANK_W", 11);
	rank_w->SetRenderMode(RENDERMODE_NONE); rank_w->SetRenderType(SCREEN);
}

void TitleUnits::Update()
{
	peopleMove[0].Update();
	peopleMove[1].Update();
	peopleMove[2].Update();

	cloudMove.Update();

	cloud->SetPosition(cloudMove.pos);

	Lerp(&peopleMove[0].pos.x, peopleMove[0].pos.x, WINSIZEX / 2.f, GetDeltaTime() * 3);
	Lerp(&peopleMove[1].pos.x, peopleMove[1].pos.x, WINSIZEX / 2.f, GetDeltaTime() * 3);
	Lerp(&peopleMove[2].pos.x, peopleMove[2].pos.x, WINSIZEX / 2.f, GetDeltaTime() * 3);

	if (!title && (abs(peopleMove[2].pos.x - WINSIZEX / 2.f) <= 10))
	{
		title = GameObject::CreateBackGround("TITLE", 1);
		title->position += Vector3(50, 20, 0);
		title->scale = Vector3(10, 10, 0);

		isBombSpawn = true;
	}
	if (title) {
		Vector3 scale = title->scale;
		Lerp(&scale, scale, Vector3(1, 1, 0), GetDeltaTime() * 10);
		title->scale = scale;

		if (!spawnBtns && (scale.x <= 2.0f))
		{
			spawnBtns = true;

			Instantiate(Button(Vector3(1150, 400, 0),
				"HOWTO", 200, 100, [&]() {
					if (howto_w->GetRenderMode() == RENDERMODE_NONE)
						howto_w->SetRenderMode(RENDERMODE_FRAME);
					else if (howto_w->GetRenderMode() == RENDERMODE_FRAME)
						howto_w->SetRenderMode(RENDERMODE_NONE);
				}));
			Instantiate(Button(Vector3(1150, 510, 0),
				"INFO", 200, 100, [&]() {
					if (info_w->GetRenderMode() == RENDERMODE_NONE)
						info_w->SetRenderMode(RENDERMODE_FRAME);
					else if (info_w->GetRenderMode() == RENDERMODE_FRAME)
						info_w->SetRenderMode(RENDERMODE_NONE);
				}));
			Instantiate(Button(Vector3(180, 570, 0),
				"RANK", 240, 114, [&]() {
					if (rank_w->GetRenderMode() == RENDERMODE_NONE)
						rank_w->SetRenderMode(RENDERMODE_FRAME);
					else if (rank_w->GetRenderMode() == RENDERMODE_FRAME)
						rank_w->SetRenderMode(RENDERMODE_NONE);
				}));

			Instantiate(Button(Vector3(1150, 620, 0),
				"QUIT", 200, 100, [&]() { PostQuitMessage(0); }));
			Instantiate(Button(Vector3(180, 430, 0),
				"START", 240, 114, [&]() { SCENE.ChangeScene("S_STAGE1"); }));
		}
	}

	if (isBombSpawn && bombSpawnTime <= GetNowTime())
	{
		Instantiate(FrameEffect(V3CENTER, IMAGE.GetImage("EXPLODE"), 0, 5, 200))->SetRenderLayer(-1);
		bombSpawnTime = GetNowTime() + 2000;
	}


	if (INPUT.GetKeyDown(VK_RETURN))
		SCENE.ChangeScene("S_TITLE");
}

void TitleUnits::Render()
{
	IMAGE.Render(peoples->GetImage(2), peopleMove[2].pos, Vector3(1, 1, 1));
	IMAGE.Render(peoples->GetImage(1), peopleMove[1].pos, Vector3(1, 1, 1));
	IMAGE.Render(peoples->GetImage(0), peopleMove[0].pos, Vector3(1, 1, 1));
}

void TitleUnits::Destroy()
{
}

void Fluffy::Update()
{
	if (IsDown) {
		pos.y += speed * GetDeltaTime();

		if (pos.y >= bottom_pos)
			IsDown = false;
	}
	else {
		pos.y -= speed * GetDeltaTime();

		if (pos.y <= top_pos)
			IsDown = true;
	}
}
