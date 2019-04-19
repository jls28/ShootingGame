#include "DXUT.h"
#include "DownBullet.h"

#include "Explode.h"
#include "ExtinctEffect.h"

#include "Texture.h"

DownBullet::DownBullet(Vector3 position, float height, float speed, float damage)
	: Bullet("ENEMY", position + Vector3(0, -height, 0), Vector3(0, 1, 0), speed, damage)
{
	endY = position.y;
}


DownBullet::~DownBullet()
{
}

void DownBullet::Init()
{
	ringSpawnTime = ringDelay * 2 + GetNowTime();

	warningEft = IMAGE.GetImage("DROP_EFT");

	warningFrame.SetFrame(0, 1, 200);

	SetTexture("ENEMY_BULLET2");
	UseCenter(texture->GetImage(1));
	SetRenderLayer(2);
}

void DownBullet::Update()
{
	if (ringSpawnTime <= GetNowTime())
	{
		float rot = GetRotation(m_direcition);
		Instantiate(ExtinctEffect("ENEMY_RING", position, rot));

		ringSpawnTime = GetNowTime() + ringDelay;
	}

	warningFrame.delay = abs(endY - position.y);

	warningFrame.delay >= 500 ? 170 : warningFrame.delay;
	warningFrame.delay <= 100 ? 50 : warningFrame.delay;

	warningFrame.OnFrame();
	m_position.y += m_speed * GetDeltaTime();

	m_rotation += GetDeltaTime() * 120;

	if (m_rotation >= 360)
		m_rotation = 0;

	if (position.y >= endY)
	{
		Instantiate(Explode(position, "ENEMY", 0.7, m_damage));
		Kill();
	}
}

void DownBullet::Render()
{
	IMAGE.Render(warningEft->GetImage(warningFrame.nowFrame),
		Vector3(position.x, endY, 0), Vector3(1, 1, 1));
}

void DownBullet::Destroy()
{
}
