#include "DXUT.h"
#include "SpawnEffect.h"

#include "Texture.h"

SpawnEffect::SpawnEffect(GameObject * obj, int cycle, Vector3 position, const string& text)
	: GameObject(OBJKIND::OBJ_EFFECT), m_object(obj), m_endCycle(cycle)
{
	SetAutoManaged(false);
	m_position = position;
	SetTexture(text);
}

SpawnEffect::~SpawnEffect()
{
}

void SpawnEffect::Init()
{
	UseCenter(texture);
	UseFrame(0, texture->size() - 1, 200);

	SetRenderLayer(2);

	if (position == V3ZERO)
		position = m_object->position;
}

void SpawnEffect::Update()
{
	if(m_frame.OnFrame() && m_frame.nowFrame == m_frame.startFrame)
	{
		m_cycle++;

		if (m_cycle == m_endCycle)
		{
			OBJECT.AddObject(m_object);
			Kill();
			m_object = nullptr;
		}
	}
}

void SpawnEffect::Render()
{
	IMAGE.Render(texture->GetImage(m_frame.nowFrame), position, scale, 0, 0xffffffff);
}

void SpawnEffect::Destroy()
{
	SAFE_DESTROY_AUTO(m_object);
}

void SpawnEffect::OnCollision(Collider * col)
{
}
