#pragma once
#include "Scene.h"
class Stage1 :
	public Scene
{
public:
	Stage1();
	virtual ~Stage1();

	virtual void Inspector() override;

	void Init();

	void CreateTriggers();
	void CreateObstacles();
};

