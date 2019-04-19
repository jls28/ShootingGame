#pragma once
#include "GameObject.h"
class ScreenEffect :
	public GameObject
{
private:
	long alpha;
	bool downMode;
public:
	ScreenEffect(Texture* tex);
	virtual ~ScreenEffect();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

public:
	static int screenEftCount;
};