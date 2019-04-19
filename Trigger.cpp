#include "DXUT.h"
#include "Trigger.h"


Trigger::Trigger(Vector3 pos, float range, const string& targetTag,
	std::function<bool(Trigger*)> func)
	: GameObject(OBJKIND::OBJ_TRIGGER), m_targetTag(targetTag), m_func(func)
{
	position = pos;
	UseCollider(range);
}

Trigger::Trigger(Vector3 pos, float width, float height, const string & targetTag,
	std::function<bool(Trigger*)> func)
	: GameObject(OBJKIND::OBJ_TRIGGER), m_targetTag(targetTag), m_func(func)
{
	position = pos;
	UseCollider(width, height);
}

Trigger::~Trigger()
{
}

void Trigger::Init()
{
	isInsideUnit = false;
	thisFrameEnd = false;
}

void Trigger::Update()
{
	if (m_collider->frameCheck == false)
		isInsideUnit = false;

	thisFrameEnd = false;
}

void Trigger::Render()
{
}

void Trigger::Destroy()
{
}

void Trigger::OnCollision(Collider * col)
{
	if (col->gameObject->tag == m_targetTag)
	{
		if (m_func(this))
			Kill();
		isInsideUnit = true;
		thisFrameEnd = true;
	}
	else if (thisFrameEnd == false)
		isInsideUnit = false;
}
