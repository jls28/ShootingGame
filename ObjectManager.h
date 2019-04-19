#pragma once
#include "Singleton.h"

enum OBJKIND
{
	OBJ_BACKGROUND,
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_GUN,
	OBJ_BULLET,
	OBJ_SPAWNER,
	OBJ_EFFECT,
	OBJ_TRIGGER,
	OBJ_UI,
	OBJ_END
};

enum SORTING_MODE
{
	SORT_Y = 1 << 0,
	SORT_LAYER = 1 << 1
};

class GameObject;
class ObjectManager :
	public Singleton<ObjectManager>
{
private:
	list<GameObject*> m_objects[OBJ_END];
	list<GameObject*> m_renders[2];

	INT m_sorting = SORT_Y | SORT_LAYER;
public:
	ObjectManager();
	virtual ~ObjectManager();

	template<class T>
	T* AddObject(T* obj)
	{
		obj->AutoManaged_Init();
		obj->Init();
		m_objects[obj->objectKind].push_back(obj);

		return obj;
	}

	void Update();
	void Render();
	void Destroy();

	void SetRenderingList();
	void SetSortingMode(INT m) { m_sorting = m; }

	INT GetListSize(INT kind) { return m_objects[kind].size(); }

	GameObject* FindGameObject(const string& tag);
};

#define OBJECT (*ObjectManager::Instance())

#define Instantiate(obj) OBJECT.AddObject(new obj)