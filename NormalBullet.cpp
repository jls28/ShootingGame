#include "DXUT.h"
#include "NormalBullet.h"

#include "ExtinctEffect.h"
#include "LifeUnit.h"
#include "FrameEffect.h"
#include "Texture.h"

NormalBullet::NormalBullet(const string & shooter_tag, Vector3 start, Vector3 dir, float speed, float damage)
	: Bullet(shooter_tag, start, dir, speed, damage)
{
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Init()
{
	UseCollider(10);
	UseCenter(texture);
	SetRenderLayer(1);

	ringSpawnTime = ringDelay * 2 + GetNowTime();
	rotation	  = GetRotation(m_direcition);
}

void NormalBullet::Update()
{
	if (ringSpawnTime <= GetNowTime())
	{
		rotation = GetRotation(m_direcition);
		Instantiate(ExtinctEffect(eftImg, position, rotation));

		ringSpawnTime = GetNowTime() + ringDelay;
	}

	Vector3 move(0, 0, 0);

	move = m_direcition * m_speed * GetDeltaTime() + position;

	if (!COL_PX.PXGetCollisionFlag(&move))
	{
		position = move;
	}
	else
	{
		Kill();
		if (eftSound.size() != 0)
			SOUND.DuplicateDistancePlay(eftSound, position);

		if (wallImg.size() != 0)
		{
			Texture* tex = IMAGE.GetImage(wallImg);
			Instantiate(FrameEffect(position, tex, 0, tex->size() - 1, 100, rotation - 180))->SetRenderLayer(2);
		}
	}
}

void NormalBullet::Render()
{
}

void NormalBullet::Destroy()
{

}

void NormalBullet::OnCollision(Collider * col)
{
	if (col->gameObject->tag == "PLAYER" || col->gameObject->tag == "ENEMY")
	{
		LifeUnit* tar = reinterpret_cast<LifeUnit*>(col->gameObject);

		if (tar->tag == m_shooter)
			return;
		else
		{
			Kill();
			tar->OnDamage(m_damage);

			if (eftSound.size() != 0)
				SOUND.DuplicateDistancePlay(eftSound, position);

			if (targetImg.size() != 0)
			{
				Texture* tex = IMAGE.GetImage(targetImg);
				Instantiate(FrameEffect(position, tex, 0, tex->size() - 1, 100, rotation - 180))->SetRenderLayer(2);
			}
		}
	}
}

void NormalBullet::TextureSet(const string & bulletImg, const string & eftImg)
{
	SetTexture(bulletImg);
	NormalBullet::eftImg = eftImg;
	UseCenter(texture);
}

void NormalBullet::SoundSet(const string & eftSound)
{
	NormalBullet::eftSound = eftSound;
}

void NormalBullet::CollideSet(const string & wall, const string & target)
{
	wallImg = wall;
	targetImg = target;
}
