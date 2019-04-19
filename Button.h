#pragma once
#include "GameObject.h"

enum BUTTON_STATE
{
	IDLE,
	MOUSE,
	DOWN,
	CLICK
};

class Button :
	public GameObject
{
private:
	function<void()> func;

	RECT range;
	INT state;
public:
	Button(Vector3 pos, const string& text, float width, float height,
		function<void()> func);
	virtual ~Button();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	bool IsInside();
};

