#include "DXUT.h"
#include "MouseCursor.h"


MouseCursor::MouseCursor(const string& imageKey)
	: GameObject(OBJKIND::OBJ_UI)
{
	SetTexture(imageKey);
}


MouseCursor::~MouseCursor()
{
}

void MouseCursor::Init()
{
	ShowCursor(false);

	SetRenderType(SCREEN);
	SetRenderLayer(20);
}

void MouseCursor::Update()
{
	position = INPUT.GetScreenMouse();

	if (INPUT.GetKeyDown(VK_LBUTTON))
		scale = Vector3(0.5, 0.5, 0.5);

	D3DXVec3Lerp(&m_scale, &m_scale, &Vector3(1.3, 1.3, 1.3), 0.2);
}

void MouseCursor::Destroy()
{
	ShowCursor(true);
}
