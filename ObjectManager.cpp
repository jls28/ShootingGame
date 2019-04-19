#include "DXUT.h"
#include "ObjectManager.h"

#include "GameObject.h"

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	Destroy();
}

void ObjectManager::Update()
{
	m_renders[SCREEN].clear();
	m_renders[SCROLL].clear();

	for (int i = 0; i < OBJKIND::OBJ_END; i++)
	{
		list<GameObject*>& ref = m_objects[i];

		for (auto iter = ref.begin(); iter != ref.end();)
		{
			auto &obj = (*iter);

			if (obj->IsDead())
			{
				SAFE_DESTROY_AUTO(obj);
				iter = ref.erase(iter);
			}
			else
			{
				obj->AutoManaged_Update();
				obj->Update();

				if (!(obj->renderMode & RENDERMODE_NONE))
				{
					if (obj->renderType == SCREEN)
						m_renders[SCREEN].push_back(obj);
					else if(obj->renderType == SCROLL)
						m_renders[SCROLL].push_back(obj);
				}
				iter++;
			}
		}
	}
	SetRenderingList();
}

void ObjectManager::Render()
{
	IMAGE.Begin(false);

	for (auto obj : m_renders[SCROLL]) {
		obj->AutoManaged_Render();
		obj->Render();
	}

	IMAGE.End();

	IMAGE.Begin(true);

	for (auto obj : m_renders[SCREEN]) {
		obj->AutoManaged_Render();
		obj->Render();
	}

	IMAGE.End();
}

void ObjectManager::Destroy()
{
	for (int i = 0; i < OBJKIND::OBJ_END; i++)
	{
		list<GameObject*>& ref = m_objects[i];

		for (auto iter = ref.begin(); iter != ref.end();)
		{
			auto &obj = (*iter);

			SAFE_DESTROY_AUTO(obj);

			iter = ref.erase(iter);
		}

		ref.clear();
	}
}

void ObjectManager::SetRenderingList()
{
	if (m_sorting & SORT_LAYER) {
		m_renders[SCREEN].sort(GameObject::CompareLayer);
		m_renders[SCROLL].sort(GameObject::CompareLayer);
	}
	if (m_sorting & SORT_Y) {
		m_renders[SCREEN].sort(GameObject::CompareY);
		m_renders[SCROLL].sort(GameObject::CompareY);
	}
}

GameObject * ObjectManager::FindGameObject(const string & tag)
{
	for (auto iter : m_objects)
	{
		for (auto iter2 : iter)
		{
			if (iter2->GetTag() == tag)
				return iter2;
		}
	}

	return nullptr;
}
