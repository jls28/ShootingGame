#include "DXUT.h"
#include "Stage2.h"
#include "ImageLoader.h"

#include "Player.h"
#include "MouseCursor.h"
#include "MapViewer.h"

#include "Trigger.h"

#include "PolliceOffice.h"
#include "SpawnEffect.h"

#include "Mob1.h"
#include "Mob2.h"

#include "Boss.h"

#define MOVE_XY(x,y,mx,my) Vector3(x + (mx), y + (my), 0)

Stage2::Stage2()
{
}


Stage2::~Stage2()
{
}

void Stage2::Inspector()
{
	SOUND.AddSound("EXPLODE", "./Resource/Sound/explode.wav");
	SOUND.AddSound("BGM", "./Resource/Sound/bgm2.wav");
	SOUND.AddSound("BOSS_BGM", "./Resource/Sound/boss_bgm.wav");
	SOUND.AddSound("FOOT_STEP", "./Resource/Sound/footstep.wav");
	SOUND.AddSound("LIGHT_STEP", "./Resource/Sound/light_step.wav");
	SOUND.AddSound("LASER", "./Resource/Sound/laser.wav");
	SOUND.AddSound("BAZOOKA_SHOT", "./Resource/Sound/bazooka_shot.wav");
	SOUND.AddSound("BAZOOKA_END", "./Resource/Sound/bazooka_end.wav");
	SOUND.AddSound("SPREAD", "./Resource/Sound/spread.wav");
	SOUND.AddSound("PISTOL", "./Resource/Sound/Pistol.wav");
	SOUND.AddSound("WIN", "./Resource/Sound/win.wav");
	SOUND.AddSound("LOSE", "./Resource/Sound/lose.wav");
	SOUND.AddSound("WARNING", "./Resource/Sound/warning.wav");

	auto loader = Instantiate(ImageLoader(true, [&]() {Init(); }));

	// RESOURCES

	// ===========================================================
	// OBSTACLE LOAD
	// ===========================================================

	loader->Load("HOSPITAL", "./Resource/Stage1/Boxs/h.png");
	loader->Load("POLICE_OFF", "./Resource/Stage1/Boxs/p.png");
	loader->Load("BLUE_HOUSE1", "./Resource/Stage2/obstacle/blueHouse.png");
	loader->Load("BLUE_HOUSE2", "./Resource/Stage2/obstacle/blueHouse2.png");
	loader->Load("BLUE_STICK", "./Resource/Stage2/obstacle/blueStick.png");
	loader->Load("GRAY_ROOF", "./Resource/Stage2/obstacle/grayRoof.png");
	loader->Load("HOUSES1", "./Resource/Stage2/obstacle/Houses1.png");
	loader->Load("HOUSES2", "./Resource/Stage2/obstacle/Houses2.png");
	loader->Load("RIGHT_BW", "./Resource/Stage2/obstacle/rightBW.png");
	loader->Load("LEFT_BW", "./Resource/Stage2/obstacle/leftBW.png");
	loader->Load("LIGHT_HOUSE", "./Resource/Stage2/obstacle/lightHouse.png");


	// MAP LOAD

	loader->Load("MINIMAP", "./Resource/Stage2/MINIMAP.png");
	loader->Load("MAP", "./Resource/Stage2/BACK.png");
	loader->Load("MAP_FRONT", "./Resource/Stage2/FRONT.png");


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

	loader->Load("BOSS_ONOFF", "./Resource/ui/warning/onoff.png");
	loader->Load("BOSS_WARNING", "./Resource/ui/warning/%d.png", 4);

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
	loader->Load("BOSS_LASER_EFT", "./Resource/Effect/BossLaser/(%d).png", 12);

	// 보스 총알
	loader->Load("BOSS_BULLET1", "./Resource/Effect/BossBullet/bullet1.png");
	loader->Load("BOSS_BULLET2", "./Resource/Effect/BossBullet/bullet2.png");
	loader->Load("BOSS_BULLET_EFT1", "./Resource/Effect/BossBullet/ring1.png");
	loader->Load("BOSS_BULLET_EFT2", "./Resource/Effect/BossBullet/ring2.png");

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

	loader->Load("BOSS_A", "./Resource/Unit/Boss/A/(%d).png", 80);
	loader->Load("BOSS_A2", "./Resource/Unit/Boss/A2/(%d).png", 80);
	loader->Load("BOSS_W", "./Resource/Unit/Boss/W/(%d).png", 80);
	loader->Load("BOSS_D", "./Resource/Unit/Boss/D/(%d).png", 80);
	loader->Load("BOSS_R", "./Resource/Unit/Boss/R/(%d).png", 80);

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

void Stage2::Init()
{
	SOUND.Play("BGM", 1);

	// SETTING
	COL_PX.PXSetMiniMap("MINIMAP");
	COL_PX.PXSetRedScale(10);
	COL_PX.PXSetReflectPower(50.0f);
	CAMERA.SetRange(0, 0, 2500, 4000);

	// CREATING
	Instantiate(MouseCursor("CURSOR"));
	Instantiate(MapViewer("MAP_FRONT"));

	Instantiate(Player(1183, 3776, 0));

	GameObject::CreateBackGround("MAP", -1);
	//GameObject::CreateBackGround("MAP_FRONT", 0);

	CreateObstacles();
	CreateTriggers();
}

void Stage2::CreateObstacles()
{
	GameObject::CreateObstacle(Vector3(3, 0, 0), "HOUSES1");
	GameObject::CreateObstacle(Vector3(1477, 0, 0), "HOUSES2");

	GameObject::CreateObstacle(Vector3(3.000000, 616.180481, 0), "BLUE_STICK");
	GameObject::CreateObstacle(Vector3(2428.000000, 615.724243, 0), "BLUE_STICK");
	GameObject::CreateObstacle(Vector3(578.597290, 1134.951782, 0), "BLUE_STICK");
	GameObject::CreateObstacle(Vector3(1800.240479, 2144.563477, 0), "BLUE_STICK");

	GameObject::CreateObstacle(Vector3(642.000000, 1050.363159, 0), "HOSPITAL");
	GameObject::CreateObstacle(Vector3(1436.401855, 1046.678711, 0), "POLICE_OFF");
	GameObject::CreateObstacle(Vector3(640.177734, 2425.284424, 0), "BLUE_HOUSE1");
	GameObject::CreateObstacle(Vector3(1550.796387, 2526.187988, 0), "BLUE_HOUSE2");
	GameObject::CreateLayerObstacle(Vector3(0.000000, 1651.757690, 0), "LEFT_BW", 0);
	GameObject::CreateLayerObstacle(Vector3(2116.000000, 1427.443970, 0), "RIGHT_BW", 0);
	GameObject::CreateLayerObstacle(Vector3(0.000000, 2997.614014, 0), "LIGHT_HOUSE", 2);
	GameObject::CreateLayerObstacle(Vector3(1638.453125, 3080.860352, 0), "GRAY_ROOF", 2);
}

void Stage2::CreateTriggers()
{
	Instantiate(Trigger(Vector3(849.727, 1432.66, 0), 300, 200, "PLAYER",
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

	Instantiate(Trigger(Vector3(1646.73, 1416.66, 0), 300, 200, "PLAYER",
		[&](Trigger* trigger) {

		if (!PolliceOffice::IsSpawn)
			Instantiate(PolliceOffice(trigger));
		return false;
	}));


	// 1
	Instantiate(Trigger(Vector3(1313.07, 2669.5, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1313.07, 2669.5, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1313.07, 2669.5, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1313.07, 2669.5, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1313.07, 2669.5, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1313.07, 2669.5, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	// 2
	Instantiate(Trigger(Vector3(1248.12, 1244.7, 0), 700, 100, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1248.12, 1244.7, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1248.12, 1244.7, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1248.12, 1244.7, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1248.12, 1244.7, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1248.12, 1244.7, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));


	Instantiate(Trigger(Vector3(406, 2704.27, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(406, 2704.27, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(406, 2704.27, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(406, 2704.27, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(406, 2704.27, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(406, 2704.27, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	Instantiate(Trigger(Vector3(449.554, 2078.63, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(449.554, 2078.63, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(449.554, 2078.63, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(449.554, 2078.63, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(449.554, 2078.63, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(449.554, 2078.63, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	Instantiate(Trigger(Vector3(269.413, 1451.63, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(269.413, 1451.63, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(269.413, 1451.63, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(269.413, 1451.63, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(269.413, 1451.63, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(269.413, 1451.63, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	Instantiate(Trigger(Vector3(450.293, 797.669, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(450.293, 797.669, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(450.293, 797.669, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(450.293, 797.669, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(450.293, 797.669, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(450.293, 797.669, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	Instantiate(Trigger(Vector3(1239.74, 681.593, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1239.74, 681.593, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1239.74, 681.593, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1239.74, 681.593, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1239.74, 681.593, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1239.74, 681.593, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	Instantiate(Trigger(Vector3(2085.66, 798.903, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(2085.66, 798.903, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(2085.66, 798.903, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(2085.66, 798.903, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(2085.66, 798.903, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(2085.66, 798.903, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	Instantiate(Trigger(Vector3(1828.09, 1806.48, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1828.09, 1806.48, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1828.09, 1806.48, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1828.09, 1806.48, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1828.09, 1806.48, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1828.09, 1806.48, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		return true;
	}));
	Instantiate(Trigger(Vector3(1779.64, 3430.09, 0), 250, 250, "PLAYER",
		[&](Trigger*) {
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1779.64, 3430.09, -150, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob1(MOVE_XY(1779.64, 3430.09, 100, 0), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1779.64, 3430.09, 0, 100), OBJECT.FindGameObject("PLAYER"))));
		Instantiate(SpawnEffect(new Mob2(MOVE_XY(1779.64, 3430.09, 0, -150), OBJECT.FindGameObject("PLAYER"))));

		CAMERA.distanceShake(Vector3(1779.64, 3430.09, 0), 500, 3);

		IMAGE.PrintLog("Enemies found you!");

		Instantiate(Trigger(Vector3(1250, 2000, 0), 800, 2000, "PLAYER",
			[&](Trigger*) {

			if (OBJECT.GetListSize(OBJ_ENEMY) == 0) {
				Instantiate(SpawnEffect(new Boss(1250, 2000, OBJECT.FindGameObject("PLAYER"))));
				return true;
			}
			else return false;
		}));

		return true;
	}));

}