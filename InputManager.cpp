#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	memset(m_oldKey, 0, sizeof(m_oldKey));
	memset(m_curKey, 0, sizeof(m_curKey));
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		m_oldKey[i] = m_curKey[i];
		m_curKey[i] = bool(GetAsyncKeyState(i));
	}
}

bool InputManager::GetKeyDown(int key)
{
	return !m_oldKey[key] && m_curKey[key];
}

bool InputManager::GetKeyUp(int key)
{
	return m_oldKey[key] && !m_curKey[key];
}

bool InputManager::GetKeyPress(int key)
{
	return m_oldKey[key] && m_curKey[key];
}

int InputManager::GetRandom(int min, int max)
{
	random_device rn;

	mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}

Vector3 InputManager::GetAxisDirection()
{
	Vector3 movePosit(0, 0, 0);

	if (INPUT.GetKeyPress(AXIS_U))
		movePosit.y -= 1;
	if (INPUT.GetKeyPress(AXIS_L))
		movePosit.x -= 1;
	if (INPUT.GetKeyPress(AXIS_D))
		movePosit.y += 1;
	if (INPUT.GetKeyPress(AXIS_R))
		movePosit.x += 1;

	D3DXVec3Normalize(&movePosit, &movePosit);

	return movePosit;
}

Vector3 InputManager::GetScreenMouse()
{
	POINT pt;
	GetCursorPos(&pt);

	ScreenToClient(DXUTGetHWND(), &pt);

	return Vector3(pt.x, pt.y, 0);
}

Vector3 InputManager::GetScrollMouse()
{
	return GetScreenMouse() + CAMERA.GetPosition() - V3CENTER;
}
