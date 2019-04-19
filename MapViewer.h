#pragma once
#include "GameObject.h"
class MapViewer :
	public GameObject
{
private:
	Texture * playerIcon;
	Texture * enemyIcon;
	Texture * bossIcon;

	Texture * minimapData;
	Texture * worldMap;
	Texture * map;

	Texture * minimapText;

	GameObject* player;
	GameObject* boss;
	list<GameObject*> enemys;

	RECT range;

	bool tab;
public:
	MapViewer(Texture* mapTexture);
	MapViewer(const string& mapTexture) : MapViewer(IMAGE.GetImage(mapTexture)) {}
	virtual ~MapViewer();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void SetRange();

	void RegisterEnemy(GameObject* enemy);
	void RegisterPlayer(GameObject* player);
	void RegisterBoss(GameObject* boss);
	void UnRegisterBoss();
	void UnRegisterEnemy(GameObject* enemy);
	void UnRegisterPlayer();

	void MiniMapInsideRender(Vector3 position, Texture* tex);
};

