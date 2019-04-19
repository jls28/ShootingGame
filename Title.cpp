#include "DXUT.h"
#include "Title.h"

#include "ImageLoader.h"
#include "TitleUnits.h"

Title::Title()
{
}


Title::~Title()
{
}

void Title::Inspector()
{
	SOUND.AddSound("BGM", "./Resource/Sound/menu.wav");
	SOUND.AddSound("BUTTON", "./Resource/Sound/button.wav");

	auto loader = Instantiate(ImageLoader(false, Init));

	loader->Load("PEOPLES", "./Resource/ui/main/peoples/%d.png", 3);
	loader->Load("BACKGROUND", "./Resource/ui/main/bg/1.png");
	loader->Load("CLOUD", "./Resource/ui/main/bg/2.png");

	loader->Load("EXPLODE", "./Resource/ui/main/explode/(%d).png", 6);

	loader->Load("TITLE", "./Resource/ui/main/title.png");

	loader->Load("HOWTO", "./Resource/ui/main/button/HowTo(%d).png", 3);
	loader->Load("START", "./Resource/ui/main/button/Start(%d).png", 3);
	loader->Load("INFO", "./Resource/ui/main/button/Info(%d).png", 3);
	loader->Load("QUIT", "./Resource/ui/main/button/Quit(%d).png", 3);
	loader->Load("RANK", "./Resource/ui/main/button/Rank(%d).png", 3);

	loader->Load("HOWTO_W", "./Resource/ui/main/window/howto.png");
	loader->Load("INFO_W", "./Resource/ui/main/window/info.png");
	loader->Load("RANK_W", "./Resource/ui/main/window/rank.png");
}

void Title::Init()
{
	Instantiate(TitleUnits);
	GameObject::CreateBackGround("BACKGROUND", -2);

	SOUND.Play("BGM", 1);
}
