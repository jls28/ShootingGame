#include "DXUT.h"
#include "Collider.h"

#include "GameObject.h"

Collider::Collider()
{
	COLLISION.Register(this);
}


Collider::~Collider()
{
	COLLISION.UnRegister(this);
}

void Collider::SetAsBox(int range)
{
	left = -range / 2;
	right = range / 2;
	top = -range / 2;
	bottom = range / 2;
}

void Collider::SetAsBox(int width, int height)
{
	left = -width / 2;
	right = width / 2;
	top = -height / 2;
	bottom = height / 2;
}

void Collider::SetAsBox(int left, int top, int right, int bottom)
{
	Collider::left	 = -left / 2;
	Collider::right	 = right / 2;
	Collider::top	 = -top / 2;
	Collider::bottom = bottom / 2;
}

const RECT& Collider::GetWorldBox()
{
	RECT ret;

	ret.left	= left	 + gameObject->position.x;
	ret.top		= top	 + gameObject->position.y;
	ret.right	= right  + gameObject->position.x;
	ret.bottom	= bottom + gameObject->position.y;

	return ret;
}
