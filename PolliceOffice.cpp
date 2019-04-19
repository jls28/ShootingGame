#include "DXUT.h"
#include "PolliceOffice.h"

#include "Button.h"
#include "Player.h"
#include "Trigger.h"

bool PolliceOffice::IsSpawn = false;

PolliceOffice::PolliceOffice(Trigger* trigger)
	: GameObject(OBJ_UI), range(trigger)
{
	player =  reinterpret_cast<Player*>(FindGameObjectWithTag("PLAYER"));

	buttons[0] = Instantiate(Button(Vector3(370, WINSIZEY / 2, 0), "S_PISTOL", 207, 287, [&]() {
		if (DATA.GetGold() < 5)
		{
			IMAGE.PrintLog("Gold shortage!");
		}
		else
		{
			player->UseOtherGun(NORMAL);
			IMAGE.PrintLog("Changed: Pistol");
			DATA.AddGold(-5);
		}
		DeleteButtons();
	}));
	buttons[1] = Instantiate(Button(Vector3(570, WINSIZEY / 2, 0), "S_LASER", 207, 287, [&]() {
		if (DATA.GetGold() < 25)
		{
			IMAGE.PrintLog("Gold shortage!");
		}
		else
		{
			player->UseOtherGun(LASER);
			IMAGE.PrintLog("Changed: Laser Gun");
			DATA.AddGold(-25);
		}
		DeleteButtons();
	}));
	buttons[2] = Instantiate(Button(Vector3(770, WINSIZEY / 2, 0), "S_BAZOOKA", 207, 287, [&]() {
		if (DATA.GetGold() < 15)
		{
			IMAGE.PrintLog("Gold shortage!");
		}
		else
		{
			player->UseOtherGun(BAZOOKA);
			IMAGE.PrintLog("Changed: Bazooka");
			DATA.AddGold(-15);
		}
		DeleteButtons();
	}));
	buttons[3] = Instantiate(Button(Vector3(970, WINSIZEY / 2, 0), "S_SPREAD", 207, 287, [&]() {
		if (DATA.GetGold() < 15)
		{
			IMAGE.PrintLog("Gold shortage!");
		}
		else
		{
			player->UseOtherGun(SPREAD);
			IMAGE.PrintLog("Changed: Spread Gun");
			DATA.AddGold(-15);
		}
		DeleteButtons();
	}));

	IsSpawn = true;
}


PolliceOffice::~PolliceOffice()
{
	IsSpawn = false;
}

void PolliceOffice::Init()
{
	SetTexture("POLLICE_BG");
	SetPosition(V3CENTER);
	SetRenderType(SCREEN);
	UseCenter(texture);

	player->SetCanAttack(false);
	SetRenderLayer(2);
}

void PolliceOffice::Update()
{
	if (!range->IsInside())
	{
		DeleteButtons();
	}
}

void PolliceOffice::Render()
{
}

void PolliceOffice::Destroy()
{
	player->SetCanAttack(true);
}

void PolliceOffice::DeleteButtons()
{
	SAFE_KILL(buttons[0]);
	SAFE_KILL(buttons[1]);
	SAFE_KILL(buttons[2]);
	SAFE_KILL(buttons[3]);
	Kill();
}
