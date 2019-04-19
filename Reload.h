#pragma once
#include "GameObject.h"
class Reload :
	public GameObject
{
private:
	float startTime;
	float endTime;

	float barX;
	float width;

	GameObject* target;
	Vector3 offset;

	Texture* reloadText;
public:
	Reload(GameObject * target, Vector3 offset, float lifeTime);
	virtual ~Reload();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

};

