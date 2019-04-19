#include "DXUT.h"
#include "GameObject.h"

#include "Frame.h"
#include "Texture.h"
#include "SingleTexture.h"
#include "Collider.h"

GameObject::GameObject(OBJKIND kind)
	: m_objectKind(kind)
{
}

GameObject::~GameObject()
{
}

void GameObject::AutoManaged_Init()
{
	if (!autoManaged) return;

	UseFrame(0, 0, 0);
	UseCenter(m_texture);
}

void GameObject::AutoManaged_Update()
{
	if (!autoManaged) return;

	m_frame.OnFrame();
}

void GameObject::AutoManaged_Render()
{
	if (!autoManaged || !m_texture) return;

	if (renderMode & RENDERMODE_NONE)
		return;

	Vector3 r_scale(scale.x * renderFlip, scale.y, scale.z);

	if (renderMode & RENDERMODE_FRAME)
	{
		IMAGE.CenterRender(m_texture->GetImage(m_frame.nowFrame),
			position, r_scale, m_center, rotation, color);
		return;
	}

	if (renderMode & RENDERMODE_MULTIPLY)
	{
		for (int i = 0; i <= m_frame.endFrame; i++)
			IMAGE.CenterRender(m_texture->GetImage(i),
				position, r_scale, center, rotation, color);
		return;
	}
}

void GameObject::AutoManaged_Destroy()
{
	if (!autoManaged) return;

	SAFE_DELETE(m_collider);
}

float GameObject::GetRotation(Vector3 dir)
{
	return D3DXToDegree(atan2f(dir.y, dir.x));
}


GameObject * GameObject::FindGameObjectWithTag(const string & tag)
{
	return OBJECT.FindGameObject(tag);
}

void GameObject::UseCollider(float range)
{
	if (!collider)
		collider = new Collider;

	collider->SetAsBox(range);
	collider->SetGameObject(this);
}

void GameObject::UseCollider(float width, float height)
{
	if (!collider)
		collider = new Collider;

	collider->SetAsBox(width, height);
	collider->SetGameObject(this);
}

void GameObject::UseCollider(float left, float top, float right, float bottom)
{
	if (!collider)
		collider = new Collider;

	collider->SetAsBox(left, top, right, bottom);
	collider->SetGameObject(this);
}

void GameObject::UseFrame(int start, int end, float delay)
{
	m_frame.SetFrame(start, end, delay);
}

void GameObject::UseCenter(Texture * texture)
{
	if (texture)
		m_center = Vector3(texture->GetImage(1)->info.Width / 2, texture->GetImage(1)->info.Height / 2, 0);
}
