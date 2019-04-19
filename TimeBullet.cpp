#include "DXUT.h"
#include "TimeBullet.h"

#include "LifeUnit.h"
#include "FrameEffect.h"
#include "Texture.h"

TimeBullet::TimeBullet(const string& owner_tag, Vector3 start,
	Vector3 dir, float speed, float damage, float delTime)
	: Bullet(owner_tag, start, dir, speed, damage), delTime(delTime)
{
}

TimeBullet::~TimeBullet()
{

}

void TimeBullet::Init()
{
	UseCollider(50, 50);
}

void TimeBullet::Update()
{
	if (delTime <= GetNowTime())
	{
		Kill();
	}
	Vector3 move(0, 0, 0);

	move = m_direcition * m_speed * GetDeltaTime() + position;

	if (!COL_PX.PXGetCollisionFlag(&move))
	{
		position = move;
	}
	else {
		Kill();
		if (wallImg.size() != 0) {

			Texture* tex = IMAGE.GetImage(wallImg);
			Instantiate(FrameEffect(position, tex, 0, tex->size() - 1,
				100, GetRotation(m_direcition) - 180))->SetRenderLayer(2);
		}
	}
}

void TimeBullet::Render()
{

}

void TimeBullet::Destroy()
{

}

void TimeBullet::OnCollision(Collider * col)
{
	if (col->gameObject->tag == "PLAYER" || col->gameObject->tag == "ENEMY")
	{
		LifeUnit* tar = reinterpret_cast<LifeUnit*>(col->gameObject);

		if (tar->tag == m_shooter)
			return;
		else
		{
			auto find = targetDelay.find(tar);

			if (find == targetDelay.end())
			{
				tar->OnDamage(m_damage);

				if (targetImg.size() != 0) {
					Texture* tex = IMAGE.GetImage(targetImg);

					Instantiate(FrameEffect(position, tex, 0, tex->size() - 1,
						100, GetRotation(m_direcition) - 180))->SetRenderLayer(2);
					targetDelay.insert(make_pair(tar, 0));
				}
			}
		}
	}
}

void TimeBullet::CollideSet(const string & wall, const string & target)
{
	wallImg = wall;
	targetImg = target;
}

