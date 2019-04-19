#include "DXUT.h"
#include "SceneManager.h"

#include "Scene.h"

SceneManager::SceneManager()
	: m_nowScene(nullptr), m_nextScene(nullptr)
{

}


SceneManager::~SceneManager()
{
	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
}

void SceneManager::Update()
{
	if (m_nextScene)
	{
		if (m_nowScene)
		{
			OBJECT.Destroy();
			IMAGE.ImageClear();
			SOUND.DeleteAllSound();
		}

		CAMERA.Init();
		m_nextScene->Inspector();
		m_nowScene = m_nextScene;

		m_nextScene = nullptr;
	}

	if (m_nowScene)
	{
		OBJECT.Update();
		COLLISION.CheckCollision();
	}
}

void SceneManager::Render()
{
	if (m_nowScene)
	{
		OBJECT.Render();
	}
}

void SceneManager::AddScene(const string & key, Scene * ptr)
{
	auto find = m_scenes.find(key);
	
	if (find != m_scenes.end())
	{
		return;
	}
	m_scenes.insert(make_pair(key, ptr));
}

void SceneManager::ChangeScene(const string & key)
{
	auto find = m_scenes.find(key);

	if (find != m_scenes.end())
	{
		m_nextScene = find->second;
	}
}
