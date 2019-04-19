#pragma once
#include "Singleton.h"

class MapViewer;
class Collider;
class CollisionManager :
	public Singleton<CollisionManager>
{
private:
	list<Collider*> m_colliders;
public:
	CollisionManager();
	virtual ~CollisionManager();

	void Register(Collider* col);
	void UnRegister(Collider* col);

	void CheckCollision();

	void Clear();

public:
	// PX : Pixel map collision module

	struct PXSYSTEM {

		void PXGetReflection(Vector3 *position, Vector3 movePosit);
		void PXSetReflectPower(float pwr) { reflectPower = pwr; }
		void PXSetMiniMap(const string& imgKey);
		void PXSetMiniMap(Texture* texture);
		void PXSetRedScale(int red = 10 /* DEFAULT SCALE == 10 */);
		bool PXGetCollisionFlag(Vector3 *destination);
		MapViewer* GetMapViewer() { return mapViewer; }
		void SetMapViewer(MapViewer* viewer) { mapViewer = viewer; }

	public:

		int redScale = 10;
		float reflectPower = 100.0f;
		Texture* miniMap = nullptr;
		MapViewer* mapViewer = nullptr;

	};

	PXSYSTEM pxSystem;
	PXSYSTEM& GetPX() { return pxSystem; }
};

#define COLLISION	(*CollisionManager::Instance())
#define COL_PX		(COLLISION.GetPX())