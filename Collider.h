#pragma once

class GameObject;
class Collider : public RECT
{
public:
	GameObject * gameObject;
	bool frameCheck = false;

public:
	Collider();
	virtual ~Collider();

	void SetAsBox(int range);
	void SetAsBox(int width, int height);
	void SetAsBox(int left, int top, int right, int bottom);

	void SetGameObject(GameObject* obj) { gameObject = obj; }

	const RECT& GetWorldBox();
};

