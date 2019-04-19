#include "DXUT.h"
#include "ExtinctEffect.h"


ExtinctEffect::ExtinctEffect(const string& texName, Vector3 pos, float rot)
	: GameObject(OBJKIND::OBJ_EFFECT)
{
	position = pos;
	rotation = rot;

	SetTexture(texName);
	UseCenter(texture);
}

ExtinctEffect::~ExtinctEffect()
{
}

void ExtinctEffect::Init()
{
	scale = Vector3(1.0f, 1.0f, 1.0f);

	SetRenderLayer(2);
}

void ExtinctEffect::Update()
{
	Lerp(&m_scale, m_scale, Vector3(0.0f, 0.0f, 0.0f), GetDeltaTime() * 5);

	if (scale.x <= 0.25f)
		Kill();
}

void ExtinctEffect::Render()
{
}

void ExtinctEffect::Destroy()
{
}
