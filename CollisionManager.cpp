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
		// 미니맵 데이터 예외처리
		*position += movePosit;
		return;
	}

	// 대상 위치 설정 : 현재 위치 + 이동할 벡터 / 배율
	Vector3 pos = (*position + movePosit) / (redScale);

	D3DLOCKED_RECT lockRect;

	miniMap->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lockRect.pBits);

	int x = (int)(pos.x);
	int y = (int)(pos.y);
	int tW = miniMap->info.Width;
	int tH = miniMap->info.Height;

	// 맵을 벗어날 시의 예외처리
	if (x < 0 || y < 0 || x > tW || y > tH)
	{
		miniMap->texturePtr->UnlockRect(0);
		return;
	}

	// 해당 비트 컬러값을 얻어옴
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
		// 미니맵 데이터 예외처리
		return false;
	}

	// 대상 위치 설정 : 현재 위치 + 이동할 벡터 / 배율
	Vector3 pos = (*destination) / (redScale);

	D3DLOCKED_RECT lockRect;
	BOOL ret;

	miniMap->texturePtr->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);
	DWORD* dwColor = reinterpret_cast<DWORD*>(lockRect.pBits);

	int x = (int)(pos.x);
	int y = (int)(pos.y);
	int tW = miniMap->info.Width;
	int tH = miniMap->info.Height;

	// 맵을 벗어날 시의 예외처리
	if (x < 0 || y < 0 || x > tW || y > tH)
	{
		miniMap->texturePtr->UnlockRect(0);
		return true;
	}

	// 해당 비트 컬러값을 얻어옴
	D3DXCOLOR color = dwColor[y * tW + x];

	if (color == D3DXCOLOR(0, 0, 0, 1))
	{
		// 충돌

		ret = true;
	}
	else
	{
		// 비 충돌

		ret = false;
	}

	miniMap->texturePtr->UnlockRect(0);

	return ret;
}
