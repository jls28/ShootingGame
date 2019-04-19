#include "DXUT.h"
#include "ImageLoader.h"

#include "GageBar.h"

ImageLoader::ImageLoader(bool isSoundPlay, function<void()> _endFunc)
	: GameObject(OBJKIND::OBJ_SPAWNER), endFunc(_endFunc), sceneName(sceneName), isPlayBgm(isSoundPlay)
{
	//autoManaged = false;
	SetPosition(Vector3(WINSIZEX / 2, 630, 0));
	SetRenderType(SCREEN);
	SetRenderLayer(4);
}

ImageLoader::~ImageLoader()
{
}

void ImageLoader::Init()
{
	curImage = 0;
	maxImage = loader.size();

	IMAGE.AddImage("L_BACKGROUND", "./Resource/ui/loading/background.png");
	IMAGE.AddImage("L_LOADBAR", "./Resource/ui/loading/%d.png", 2);

	gageBar = Instantiate(GageBar("L_LOADBAR", m_position, maxImage, curImage));
	gageBar->SetRenderType(SCREEN);

	backGround = GameObject::CreateBackGround("L_BACKGROUND", 2);
	backGround->SetRenderType(SCREEN);


	if (isPlayBgm) {
		SOUND.AddSound("LOADING", "./Resource/Sound/loading.wav");
		SOUND.Play("LOADING", 1);
	}
}

void ImageLoader::Update()
{
	maxImage = loader.size();
	IMAGE.AddImage(loader[curImage].key, loader[curImage].path, loader[curImage].count);

	if (++curImage >= maxImage)
	{
		endFunc();
		Kill();
		curImage--;

		if (gageBar) Kill(gageBar);
		if (backGround) Kill(backGround);
	}
}


void ImageLoader::Render()
{
	//IMAGE.Render(m_texture, V3CENTER, m_scale);

	IMAGE.PrintCenterText(to_string(
		(int)(((float)curImage / (float)maxImage) * 100)) + "%",
		Vector3(WINSIZEX / 2 + 10, 632, 0), 75, D3DCOLOR_ARGB(245, 93, 85, 78));
}

void ImageLoader::Destroy()
{
	if (isPlayBgm)
		SOUND.Stop("LOADING");
}

void ImageLoader::Load(const string & key, const string & path, int count)
{
	loader.push_back(LOAD_INFO(key, path, count));
}
