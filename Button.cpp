#include "DXUT.h"
#include "Button.h"

#include "Texture.h"

Button::Button(Vector3 pos, const string& text, float width, float height, function<void()> func)
	: GameObject(OBJ_UI), func(func)
{
	m_position = pos;
	SetTexture(text);
	range = { -(LONG)width / 2, -(LONG)height / 2,(LONG)width / 2,(LONG)height / 2 };
	SetRenderLayer(3);
	SetRenderType(SCREEN);

	SetAutoManaged(false);

	UseCenter(texture->GetImage(1));
}

Button::~Button()
{
}

void Button::Init()
{
	state = IDLE;
}

void Button::Update()
{
	bool inside = IsInside();

	if (inside)
	{
		if (state == IDLE || state == CLICK)
			state = MOUSE;
	}
	else
		state = IDLE;

	if (INPUT.GetKeyPress(VK_LBUTTON))
	{
		if (inside)
			state = DOWN;
		else
			state = IDLE;
	}

	if (state == DOWN)
		if (INPUT.GetKeyUp(VK_LBUTTON))
		{
			if (inside) {
				func();
				SOUND.DuplicatePlay("BUTTON");
				state = CLICK;
			}
		}

	if (state == MOUSE)
		Lerp(&m_scale, m_scale, Vector3(1.2, 1.2, 1.2), 7 * DXUTGetElapsedTime());
	else
		Lerp(&m_scale, m_scale, Vector3(1.0, 1.0, 1.0), 7 * DXUTGetElapsedTime());
}

void Button::Render()
{
	IMAGE.Render(texture->GetImage(state == CLICK ? IDLE : state), position, scale);
}

void Button::Destroy()
{
}

bool Button::IsInside()
{
	bool result;
	Vector3 mouse;

	if (m_renderType == SCREEN)
		mouse = INPUT.GetScreenMouse();
	else if(m_renderType == SCROLL)
		mouse = INPUT.GetScrollMouse();

	return (range.left + m_position.x <= mouse.x &&
		range.right + m_position.x >= mouse.x &&
		range.top + m_position.y <= mouse.y &&
		range.bottom + m_position.y >= mouse.y);
}
