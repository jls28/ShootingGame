#include "DXUT.h"
#include "FrameEffect.h"

#include "Texture.h"

FrameEffect::FrameEffect(Vector3 position, Texture* text, int start, int end, DWORD delay, float rot)
	: GameObject(OBJKIND::OBJ_EFFECT)
{
	m_position = position;
	m_rotation = rot;

	UseFrame(start, end, delay);
	SetTexture(text);
	UseCenter(texture->GetImage(1));

	SetAutoManaged(false);
}

FrameEffect::~FrameEffect()
{
}

void FrameEffect::Init()
{
}

void FrameEffect::Update()
{
	if (m_frame.OnFrame() && m_frame.nowFrame == m_frame.endFrame)
	{
		Kill();
	}
}

void FrameEffect::Render()
{
	IMAGE.Render(texture->GetImage(m_frame.nowFrame), position, scale, rotation, color);
}

void FrameEffect::Destroy()
{
}
