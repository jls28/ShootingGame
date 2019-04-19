#pragma once
#include "Singleton.h"

class Scene;
class SceneManager :
	public Singleton<SceneManager>
{
private:
	map<string, Scene*> m_scenes;
public:
	SceneManager();
	virtual ~SceneManager();

	void Update();
	void Render();

public:
	Scene * m_nowScene;
	Scene * m_nextScene;

	void AddScene(const string& key, Scene* ptr);
	void ChangeScene(const string& key);
};

#define SCENE (*SceneManager::Instance())