#pragma once
#include "Singleton.h"

// InputManager::GetAxisDirection() : FUNC

#define AXIS_U 'W'
#define AXIS_L 'A'
#define AXIS_D 'S'
#define AXIS_R 'D'


class InputManager :
	public Singleton<InputManager>
{
private:

	bool m_oldKey[256];
	bool m_curKey[256];

public:
	InputManager();
	virtual ~InputManager();

	void Update();

	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
	bool GetKeyPress(int key);

	int GetRandom(int min, int max);

	Vector3 GetAxisDirection();

	Vector3 GetScreenMouse();
	Vector3 GetScrollMouse();
};

#define INPUT (*InputManager::Instance())