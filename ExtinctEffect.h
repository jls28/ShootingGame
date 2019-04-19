#pragma once
#include "GameObject.h"
class ExtinctEffect :
	public GameObject
{
private:
	
public:
	ExtinctEffect(const string& texName, Vector3 pos, float rot = 0.0f);
	~ExtinctEffect();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;
};

