#pragma once
#include "Scene.h"
class Stage2 :
	public Scene
{
public:
	Stage2();
	virtual ~Stage2();

	virtual void Inspector() override;

	void Init();
	void CreateObstacles();
	void CreateTriggers();
};

