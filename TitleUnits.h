#pragma once
#include "GameObject.h"

struct Fluffy
{
	float top_pos;
	float bottom_pos;
	Vector3 pos;
	bool IsDown = true;
	float speed;

	Fluffy() {}
	Fluffy(Vector3 pos, float top, float bottom, float speed) 
		: top_pos(top), bottom_pos(bottom), IsDown(true), speed(speed), pos(pos) {
	}

	void Update();
};

class TitleUnits
	: public GameObject
{
private:
	Texture * peoples;

	Fluffy peopleMove[3];
	Fluffy cloudMove;

	GameObject* cloud;
	GameObject* title;

	GameObject* howto_w = nullptr;
	GameObject* info_w = nullptr;
	GameObject* rank_w = nullptr;

	bool spawnBtns = false;

	bool isBombSpawn = false;
	float bombSpawnTime = 0;
public:
	TitleUnits();
	~TitleUnits();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

};

