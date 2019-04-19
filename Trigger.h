#pragma once
#include "GameObject.h"
class Trigger :
	public GameObject
{
private:
	std::function<bool(Trigger*)> m_func;
	string m_targetTag;

	bool isInsideUnit;
	bool thisFrameEnd;
public:
	Trigger(Vector3 pos, float range, const string& targetTag, std::function<bool(Trigger*)> func);
	Trigger(Vector3 pos, float width, float height, const string& targetTag, std::function<bool(Trigger*)> func);
	virtual ~Trigger();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void OnCollision(Collider* col) override;

	bool IsInside() { return isInsideUnit; }
};

