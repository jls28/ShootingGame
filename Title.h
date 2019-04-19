#pragma once
#include "Scene.h"
class Title :
	public Scene
{
private:

public:
	Title();
	virtual ~Title();

	virtual void Inspector() override;

	static void Init();
};

