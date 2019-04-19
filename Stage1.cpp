#include "DXUT.h"
#include "Stage1.h"
#include "ImageLoader.h"

#include "Player.h"
#include "Enemy.h"
#include "MouseCursor.h"
#include "MapViewer.h"
#include "Trigger.h"

#include "SpawnEffect.h"
#include "Mob1.h"
#include "Mob2.h"
#include "Boss.h"

#include "PolliceOffice.h"

#define MOVE_XY(x,y,mx,my) Vector3(x + (mx), y + (my), 0)

Stage1::Stage1()
{
}


Stage1::~Stage1()
{
}

void Stage1::Inspector()
{
	SOUND.AddSound("EXPLODE"		,	"./Resource/Sound/explode.wav"		);
	SOUND.AddSound("BGM"			,	"./Resource/Sound/bgm1.wav"			);
	SOUND.AddSound("FOOT_STEP"		,	"./Resource/Sound/footstep.wav"		);
	SOUND.AddSound("LIGHT_STEP"		,	"./Resource/Sound/light_step.wav"	);
	SOUND.AddSound("LASER"			,	"./Resource/Sound/laser.wav"		);
	SOUND.AddSound("BAZOOKA_SHOT"	,	"./Resource/Sound/bazooka_shot.wav"	);
	SOUND.AddSound("BAZOOKA_END"	,	"./Resource/Sound/bazooka_end.wav"	);
	SOUND.AddSound("SPREAD"			,	"./Resource/Sound/spread.wav"		);
	SOUND.AddSound("PISTOL"			,	"./Resource/Sound/Pistol.wav"		);
	
	auto loader = Instantiate(ImageLoader(true, [&]() {Init(); }));

	// RESOURCES


	// ===========================================================
	// OBSTACLE LOAD
	// ===========================================================

	loader->Load("RED_BOX", "./Resource/Stage1/Boxs/redBox.png");
	loader->Load("BLUE_BOX", "./Resource/Stage1/Boxs/blueBox.png");
	loader->Load("WOOD_BOX", "./Resource/Stage1/Boxs/woodBox.png");
	loader->Load("HOSPITAL", "./Resource/Stage1/Boxs/h.png");
	loader->Load("POLICE_OFF", "./Resource/Stage1/Boxs/p.png");
	loader->Load("BOXS", "./Resource/Stage1/Boxs/Boxs%d.png", 4);

	// MAP LOAD

	loader->Load("MINIMAP", "./Resource/Stage1/MINIMAP.png");
	loader->Load("MAP", "./Resource/Stage1/BACK.png");
	loader->Load("MAP_FRONT", "./Resource/Stage1/CONTAINER.png");

	// ===========================================================
	// UI LOAD
	// ===========================================================

	loader->Load("CURSOR", "./Resource/Cursor/Cursor.png");
	loader->Load("HPBAR", "./Resource/ui/bar%d.png", 3);

	loader->Load("LARGE_BULLETBAR", "./Resource/ui/ingame/LargeBullet.png");
	loader->Load("LARGE_HPBAR", "./Resource/ui/ingame/LargeHp.png");
	loader->Load("LARGE_PANEL", "./Resource/ui/ingame/LargeBar.png");
	loader->Load("GOLD_PANEL", "./Resource/ui/ingame/gold.png");

	loader->Load("PISTOL_UI", "./Resource/ui/gun_ui/normal.png");
	loader->Load("BAZOOKA_UI", "./Resource/ui/gun_ui/bazooka.png");
	loader->Load("LASER_UI", "./Resource/ui/gun_ui/laser.png");
	loader->Load("SPREAD_UI", "./Resource/ui/gun_ui/spread.png");

	loader->Load("RELOAD", "./Resource/ui/reload/%d.png", 2);
	loader->Load("RELOAD_T", "./Resource/ui/reload/reload.png");
	loader->Load("RECOVERY_T", "./Resource/ui/reload/recovery.png");

	loader->Load("S_PISTOL", "./Resource/ui/ingame/s_pistol.png");
	loader->Load("S_LASER", "./Resource/ui/ingame/s_laser.png");
	loader->Load("S_BAZOOKA", "./Resource/ui/ingame/s_bazooka.png");
	loader->Load("S_SPREAD", "./Resource/ui/ingame/s_spread.png");
	loader->Load("POLLICE_BG", "./Resource/ui/ingame/pollice_bg.png");

	loader->Load("CLEAR", "./Resource/ui/end/clear.png");
	loader->Load("GAMEOVER", "./Resource/ui/end/gameover.png");

	loader->Load("RE_BUTTON", "./Resource/ui/end/re(%d).png", 3);
	loader->Load("MAIN_BUTTON", "./Resource/ui/end/main(%d).png", 3);
	

	// ===========================================================
	// EFFECT LOAD
	// ===========================================================


	// 스폰 이펙트
	loader->Load("SPAWN_EFT", "./Resource/Effect/Spawn/(%d).png", 3);

	// 기본 총알
	loader->Load("NORMAL_BULLET", "./Resource/Effect/NormalBullet/bullet.png");
	loader->Load("RING_EFT", "./Resource/Effect/NormalBullet/ring.png");

	// 퍼지는 총알
	loader->Load("SPREAD_BULLET", "./Resource/Effect/SpreadBullet/bullet.png");
	loader->Load("SPREAD_EFT", "./Resource/Effect/SpreadBullet/ring.png");

	// 레이저
	loader->Load("LASER_EFT", "./Resource/Effect/Laser/(%d).png", 12);

	// 바주카
	loader->Load("BAZOOKA_BULLET", "./Resource/Effect/Bazooka/bullet.png");
	loader->Load("BAZOOKA_EFT", "./Resource/Effect/Bazooka/ring.png");

	loader->Load("ENEMY_BULLET", "./Resource/Effect/EnemyBullet/bullet.png");
	loader->Load("ENEMY_BULLET2", "./Resource/Effect/EnemyBullet2/bullet.png");
	loader->Load("ENEMY_RING", "./Resource/Effect/EnemyBullet2/ring.png");

	// 플레이어 뛸때 먼지
	loader->Load("DASH_EFT", "./Resource/Effect/dash.png");

	// 연기
	loader->Load("SMOKE", "./Resource/Effect/Smoke/(%d).png", 7);

	// 총알 피격

	loader->Load("RED_W_EFT", "./Resource/Effect/Attacked/red_w/(%d).png", 5);
	loader->Load("BLUE_W_EFT", "./Resource/Effect/Attacked/blue_w/(%d).png", 5);
	loader->Load("RED_T_EFT", "./Resource/Effect/Attacked/red_t/(%d).png", 2);
	loader->Load("BLUE_T_EFT", "./Resource/Effect/Attacked/blue_t/(%d).png", 4);

	// 폭발
	loader->Load("EXPLODE", "./Resource/Effect/Explode/(%d).png", 6);

	// 보스 공격 도착 위치
	loader->Load("DROP_EFT", "./Resource/Effect/DropPos/(%d).png", 2);

	// 화면 이펙트
	loader->Load("SCREEN_EFT1", "./Resource/Effect/Display/1.png");
	loader->Load("SCREEN_EFT2", "./Resource/Effect/Display/2.png");
	loader->Load("SCREEN_EFT3", "./Resource/Effect/Display/3.png");

	// ===========================================================
	// MOB LOAD ( A : attack, W : walk, D : death, R : Rush )
	// ===========================================================

	loader->Load("MOB1_A", "./Resource/Unit/Mob1/A/(%d).png", 80);
	loader->Load("MOB1_W", "./Resource/Unit/Mob1/W/(%d).png", 80);
	loader->Load("MOB1_D", "./Resource/Unit/Mob1/D/(%d).png", 80);

	loader->Load("MOB2_A", "./Resource/Unit/Mob2/A/(%d).png", 80);
	loader->Load("MOB2_W", "./Resource/Unit/Mob2/W/(%d).png", 80);
	loader->Load("MOB2_D", "./Resource/Unit/Mob2/D/(%d).png", 80);

	loader->Load("PLAYER_A_NORMAL", "./Resource/Unit/Player/A/NORMAL/(%d).png", 80);
	loader->Load("PLAYER_A_LASER", "./Resource/Unit/Player/A/LASER/(%d).png", 80);
	loader->Load("PLAYER_A_BAZOOKA", "./Resource/Unit/Player/A/BAZOOKA/(%d).png", 80);
	loader->Load("PLAYER_A_SPREAD", "./Resource/Unit/Player/A/SPREAD/(%d).png", 80);

	loader->Load("PLAYER_W_NORMAL", "./Resource/Unit/Player/W/NORMAL/(%d).png", 80);
	loader->Load("PLAYER_W_LASER", "./Resource/Unit/Player/W/LASER/(%d).png", 80);
	loader->Load("PLAYER_W_BAZOOKA", "./Resource/Unit/Player/W/BAZOOKA/(%d).png", 80);
	loader->Load("PLAYER_W_SPREAD", "./Resource/Unit/Player/W/SPREAD/(%d).png", 80);

	loader->Load("PLAYER_I_NORMAL", "./Resource/Unit/Player/I/NORMAL/(%d).png", 80);
	loader->Load("PLAYER_I_LASER", "./Resource/Unit/Player/I/LASER/(%d).png", 80);
	loader->Load("PLAYER_I_BAZOOKA", "./Resource/Unit/Player/I/BAZOOKA/(%d).png", 80);
	loader->Load("PLAYER_I_SPREAD", "./Resource/Unit/Player/I/SPREAD/(%d).png", 80);
	loader->Load("PLAYER_D", "./Resource/Unit/Player/D/(%d).png", 80);
}

void Stage1::Init()
{
	SOUND.Play("BGM", 1);
	DATA.SetGold(30);

	// SETTING
	COL_PX.PXSetMiniMap("MINIMAP");
	COL_PX.PXSetRedScale(10);
	COL_PX.PXSetReflectPower(250.0f);
	CAMERA.SetRange(0, 0, 2500, 4000);

	// CREATING
	Instantiate(MapViewer("MAP_FRONT"));
	Instantiate(MouseCursor("CURSOR"));

	Instantiate(Player(1183, 3776, 0));

	IMAGE.PrintLog("Destroy all enemies!");

	GameObject::CreateBackGround("MAP", -1);

	CreateObstacles();
	CreateTriggers();
}

void Stage1::CreateTriggers()
{
	// SETTING TRIGGERS

	Instantiate(Trigger(Vector3(1693.159180, 2296.056152, 0), 300, 200, "PLAYER",
		[&](Trigger* trigger) {
		if (!PolliceOffice::IsSpawn)
			Instantiate(PolliceOffice(trigger));

		return false;
	}));

	Instantiate(Trigger(Vector3(702.135010, 2302.499756, 0), 300, 200, "PLAYER",
		[&](Trigger* trigger) {

		if (INPUT.GetKeyDown(VK_SPACE))
		{
			if (DATA.GetGold() < 20)
			{
				IMAGE.PrintLog("Gold shortage!");
			}
			else
			{
				reinterpret_cast<Player*>(GameObject::FindGameObjectWithTag("PLAYER"))->Heal(200);
				DATA.AddGold(-20);
				IMAGE.PrintLog("Recovered (+200)");
			}
		}

		return false;
	}));

	// 1
	Instantiate(Trigger(Vector3(1189.61, 3471.88, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1189.61, 3471.88, -100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1189.61, 3471.88, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1189.61, 3471.88, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1189.61, 3471.88, 0, -100), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1189.61, 3471.88, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	// 2
	Instantiate(Trigger(Vector3(1195.61, 2872.72, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1195.61, 2872.72, -100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1195.61, 2872.72, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1195.61, 2872.72, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1195.61, 2872.72, 0, -100), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1195.61, 2872.72, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	// 3
	Instantiate(Trigger(Vector3(2053.37, 2864.66, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(2053.37, 2864.66, -100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(2053.37, 2864.66, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(2053.37, 2864.66, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(2053.37, 2864.66, 0, -100), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(2053.37, 2864.66, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	//4
	Instantiate(Trigger(Vector3(336, 2851.66, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(336, 2851.66, -100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(336, 2851.66, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(336, 2851.66, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(336, 2851.66, 0, -100), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(336, 2851.66, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	//5
	Instantiate(Trigger(Vector3(833.056, 1194.5, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(833.056, 1194.5, -100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(833.056, 1194.5, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(833.056, 1194.5, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(833.056, 1194.5, 0, -100), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(833.056, 1194.5, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	//6
	Instantiate(Trigger(Vector3(1553.36, 1180.5, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1553.36, 1180.5, -100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1553.36, 1180.5, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1553.36, 1180.5, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1553.36, 1180.5, 0, -100), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1553.36, 1180.5, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	//7
	Instantiate(Trigger(Vector3(1178.36, 613.197, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1178.36, 613.197, -100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1178.36, 613.197, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1178.36, 613.197, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1178.36, 613.197, 0, -100), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1178.36, 613.197, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));

	Instantiate(Trigger(Vector3(1250, 0, 0), 900, 300, "PLAYER",
		[&](Trigger*) {
		
		if (INPUT.GetKeyDown(VK_SPACE)) {
			if (OBJECT.GetListSize(OBJ_ENEMY) != 0)
			{
				IMAGE.PrintLog("Kill all the enemies.");
			}
			else
			{
				SCENE.ChangeScene("S_STAGE2");
			}
		}
		return false;
	}));
}

void Stage1::CreateObstacles()
{
	// CREATE OBSTACLES

	GameObject::CreateObstacle(Vector3(625.000000, 602.458740, 0), "RED_BOX");
	GameObject::CreateObstacle(Vector3(875.135498, 594.380127, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1368.747070, 591.621582, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1526.750000, 599.617676, 0), "RED_BOX");
	GameObject::CreateObstacle(Vector3(424.899414, 1067.675293, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(423.899414, 1176.675293, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(422.899414, 1287.675293, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(422.899414, 1397.675293, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(422.899414, 1505.675293, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1119.525879, 1066.757568, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1816.949219, 1063.964600, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1816.949707, 1172.964600, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1813.949707, 1281.964600, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1814.949707, 1394.592285, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1815.949707, 1502.604492, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(1407.332275, 1506.480469, 0), "RED_BOX");
	GameObject::CreateObstacle(Vector3(742.332275, 1512.480469, 0), "RED_BOX");
	GameObject::CreateObstacle(Vector3(1120.231689, 2337.397217, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(501.140991, 2756.718506, 0), "RED_BOX");
	GameObject::CreateObstacle(Vector3(751.140991, 2755.718506, 0), "BLUE_BOX");
	GameObject::CreateObstacle(Vector3(1401.423340, 2756.718506, 0), "BLUE_BOX");
	GameObject::CreateObstacle(Vector3(1649.423340, 2756.718506, 0), "BLUE_BOX");
	GameObject::CreateObstacle(Vector3(1426.824707, 3374.695801, 0), "WOOD_BOX");
	GameObject::CreateObstacle(Vector3(806.824707, 3371.697021, 0), "WOOD_BOX");

	GameObject::CreateObstacle(Vector3(258.662842, 7.000000, 0), "BOXS", 0);
	GameObject::CreateObstacle(Vector3(1579.160645, 3.000000, 0), "BOXS", 1);

	GameObject::CreateObstacle(Vector3(494.784912, 1921.477295, 0), "HOSPITAL");
	GameObject::CreateObstacle(Vector3(1487.041504, 1926.477295, 0), "POLICE_OFF");

	GameObject::CreateObstacle(Vector3(212.000000, 3237.611572, 0), "BOXS", 2);
	GameObject::CreateObstacle(Vector3(1589.548828, 3251.488281, 0), "BOXS", 3);

}
