#include "DXUT.h"
#include "Maingame.h"

#include "Title.h"
#include "Stage1.h"
#include "Stage2.h"

Maingame::Maingame()
{

}


Maingame::~Maingame()
{
}

void Maingame::Init()
{
	SCENE.AddScene("S_TITLE", new Title);
	SCENE.AddScene("S_STAGE1", new Stage1);
	SCENE.AddScene("S_STAGE2", new Stage2);

	SCENE.ChangeScene("S_TITLE");
}

void Maingame::Update()
{
	INPUT.Update();
	CAMERA.Update();
	SCENE.Update();
	IMAGE.UpdateSystemLog();
}

void Maingame::Render()
{
	CAMERA.SetTransform();

	SCENE.Render();
	IMAGE.RenderSystemLog();
}

void Maingame::Destroy()
{
	ObjectManager	::Release();
	CollisionManager::Release();
	SceneManager	::Release();
	ImageManager	::Release();
	InputManager	::Release();
	CameraManager	::Release();
	SoundManager	::Release();
	DataManager		::Release();
}

void Maingame::ResetDevice()
{
	IMAGE.ResetDevice();
}

void Maingame::LostDevice()
{
	IMAGE.LostDevice();
}
