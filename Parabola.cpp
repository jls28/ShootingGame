#include "DXUT.h"
#include "Parabola.h"


Parabola::Parabola(OBJKIND kind)
	: GameObject(kind)
{
}

Parabola::~Parabola()
{
}

void Parabola::Init()
{
}

void Parabola::Update()
{
}

void Parabola::Render()
{
}

void Parabola::Destroy()
{
}

void Parabola::Setting(Vector3 start, Vector3 dest, float maxTime, float plusHeight)
{
	position = start;

	startPos = start;
	destPos = dest;

	maxAchieveTime = maxTime;

	if (startPos.y < destPos.y)
		maxHeight = destPos.y + plusHeight;
	else
		maxHeight = startPos.y + plusHeight;

	PreCalculate();
}

void Parabola::PreCalculate()
{
	destHeight = startPos.y - destPos.y;
	height = (maxHeight - destPos.y);

	gravity = 2 * height / (maxAchieveTime * maxAchieveTime);

	speed.y = sqrt(2 * gravity * height);

	float a = gravity;
	float b = -2 * speed.y;
	float c = 2 * destHeight;

	destTime = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	speed.x = (destPos.x - startPos.x) / destTime;
}

bool Parabola::IsEnd()
{
	accrueTime += GetDeltaTime();

	position = Vector3(startPos.x + speed.x * accrueTime,
		(startPos.y - speed.y * accrueTime + 0.5f * gravity * accrueTime * accrueTime), 0);

	return accrueTime > destTime;
}
