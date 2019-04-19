#pragma once
#include "GameObject.h"
class FrameEffect :
	public GameObject
{
public:
	FrameEffect(Vector3 position, Texture* text, int start, int end, DWORD delay, float rot = 0);
	virtual ~FrameEffect();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

