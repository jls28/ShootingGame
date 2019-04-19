#include "DXUT.h"
#include "CollisionManager.h"

#include "Collider.h"
#include "GameObject.h"
#include "Texture.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	Clear();
}

void CollisionManager::Register(Collider * col)
{
	m_colliders.push_back(col);
}

void CollisionManager::UnRegister(Collider * col)
{
	m_colliders.remove(col);
}

void CollisionManager::CheckCollision()
{
	for (auto iter : m_colliders)
		iter->frameCheck = false;

	for (auto i : m_colliders)
	{
		for (auto j : m_colliders)
		{
			if (i == j) continue;

			RECT l = i->GetWorldBox();
			RECT r = j->GetWorldBox();
			RECT out;

			if (IntersectRect(&out, &l, &r))
			{
				i->gameObject->OnCollision(j);
				i->frameCheck = true;
			}
		}
	}
}

void CollisionManager::Clear()
{
	m_colliders.clear();
}

// ==================================================================
// PX SYSTEM : PIXEL MAP COLLISION MODULE
// ==================================================================

void CollisionManager::PXSYSTEM::PXGetReflection(Vector3 * position, Vector3 movePosit)
{
	if (!miniMap)
	{
		// �̴ϸ� ������ ����ó��
		*position += movePosit;
		return;
	}

	// ��� ��ġ ���� : ���� ��ġ + �̵��� ���� / ����
	Vector3 pos = (*position + movePosit) / (redScale);

	D3DLOCKED_RECT lockRect;

	miniMap->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lockRect.pBits);

	int x = (int)(pos.x);
	int y = (int)(pos.y);
	int tW = miniMap->info.Width;
	int tH = miniMap->info.Height;

	// ���� ��� ���� ����ó��
	if (x < 0 || y < 0 || x > tW || y > tH)
	{
		miniMap->texturePtr->UnlockRect(0);
		return;
	}

	// �ش� ��Ʈ �÷����� ����
	D3DXCOLOR color = dwColor[y * tW + x];

	if (color == D3DXCOLOR(0, 0, 0, 1))
	{
		Vector3 reflectVec;
		D3DXVec3Normalize(&reflectVec, &movePosit);

		*position += -reflectPower * reflectVec * GetDeltaTime();
	}
	else
	{
		*position += movePosit;
	}

	miniMap->texturePtr->UnlockRect(0);
}

void CollisionManager::PXSYSTEM::PXSetMiniMap(const string & imgKey)
{
	miniMap = IMAGE.GetImage(imgKey);
}

void CollisionManager::PXSYSTEM::PXSetMiniMap(Texture * texture)
{
	miniMap = texture;
}

void CollisionManager::PXSYSTEM::PXSetRedScale(int red)
{
	redScale = red;
}

bool CollisionManager::PXSYSTEM::PXGetCollisionFlag(Vector3 * destination)
{
	if (!miniMap)
	{
		// �̴ϸ� ������ ����ó��
		return false;
	}

	// ��� ��ġ ���� : ���� ��ġ + �̵��� ���� / ����
	Vector3 pos = (*destination) / (redScale);

	D3DLOCKED_RECT lockRect;
	BOOL ret;

	miniMap->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lockRect.pBits);

	int x = (int)(pos.x);
	int y = (int)(pos.y);
	int tW = miniMap->info.Width;
	int tH = miniMap->info.Height;

	// ���� ��� ���� ����ó��
	if (x < 0 || y < 0 || x > tW || y > tH)
	{
		miniMap->texturePtr->UnlockRect(0);
		return true;
	}

	// �ش� ��Ʈ �÷����� ����
	D3DXCOLOR color = dwColor[y * tW + x];

	if (color == D3DXCOLOR(0, 0, 0, 1))
	{
		// �浹

		ret = true;
	}
	else
	{
		// �� �浹

		ret = false;
	}

	miniMap->texturePtr->UnlockRect(0);

	return ret;
}
