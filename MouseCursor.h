#pragma once
#include "GameObject.h"
class MouseCursor :
	public GameObject
{
public:
	MouseCursor(const string& imageKey);
	virtual ~MouseCursor();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;
};

