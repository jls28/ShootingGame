#include "DXUT.h"
#include "Gun.h"

#include "Reload.h"

Gun::Gun()
	: GameObject(OBJKIND::OBJ_GUN)
{
	SetRenderLayer(1);
	SetAutoManaged(false);
}


Gun::~Gun()
{
}

void Gun::Init()
{
}

void Gun::Update()
{
	if (m_owner)
	{
		if (m_frameSkip <= GetNowTime() && m_reload)
		{
			m_reload = false;
			m_curBullet = m_maxBullet;
		}

		position = m_owner->position;
	}
}

void Gun::Render()
{
}

void Gun::Destroy()
{
}

void Gun::OnCollision(Collider * col)
{
}

Vector3 Gun::GetFirePos(float rot)
{
	return Vector3(cosf(D3DXToRadian(rot)) * m_gunLength + position.x,
		sinf(D3DXToRadian(rot)) * m_gunLength + position.y, 0);

	//return position;
}

Vector3 Gun::GetDirection(float rebound, Vector3 destination)
{
	Vector3 ret = 
		destination + Vector3(INPUT.GetRandom(-rebound, rebound),
		INPUT.GetRandom(-rebound, rebound), 0);

	ret -= (m_owner->position + m_center);

	D3DXVec3Normalize(&ret, &ret);

	return ret;
}

bool Gun::CanFire()
{
	if (m_frameSkip < GetNowTime())
	{
		if (--m_curBullet <= 0 && !m_reload)
		{
			m_frameSkip = m_maxReloadDelay + GetNowTime();
			m_reload = true;

			Instantiate(Reload(m_owner, Vector3(0, -110, 0), m_maxReloadDelay));
		}
		else
		{
			m_frameSkip = m_maxShotDelay + GetNowTime();
		}

		return true;
	}
	return false;
}

bool Gun::AutoGeneric(Vector3 destination, int key)
{
	m_direction = GetDirection(0, destination);
	rotation = GetRotation(m_direction);
	m_destination = destination;

	if ((key != AUTO_SHOT && INPUT.GetKeyPress(key)) || key == AUTO_SHOT)
	{
		return CanFire();
	}

	return false;
}

float Gun::GetRotation(Vector3 dir)
{
	return D3DXToDegree(atan2f(dir.y, dir.x));
}

void Gun::DrawInfo(const string& gunName)
{
}

void Gun::DrawLaser()
{
	Vector3 firePos = GetFirePos(rotation);
	Vector3 distance = (center + position) - firePos; // 个烹 - 醚备
	Vector3 distance2 = INPUT.GetScrollMouse() - (center + position); // 付快胶 - 个烹

	if (D3DXVec3Length(&distance) >= D3DXVec3Length(&distance2))
	{
		return;
	}
	

	Vector3 points[2] = { firePos, m_destination };

	CAMERA.ScrollToScreen(&points[0]);
	CAMERA.ScrollToScreen(&points[1]);

	Vector2 points2D[2] = { points[0],points[1] };

	IMAGE.End();
	IMAGE.Begin(true);

	IMAGE.DrawLine(points2D, 2, 5, 0, D3DCOLOR_ARGB(70, 255, 0, 0));

	IMAGE.End();
	IMAGE.Begin(false);
}

void Gun::GunSetting(float shotDelay, float reloadDelay, int maxBullet, int length, int rebound)
{
	m_maxShotDelay = shotDelay;
	m_maxReloadDelay = reloadDelay;

	m_frameSkip = 0;
	m_curBullet = m_maxBullet = maxBullet;

	m_gunLength = length;
	m_rebound = rebound;
}

void Gun::SetBulletTexture(const string & bulletEft, const string & ringEft)
{
	Gun::bulletEft = bulletEft;
	Gun::ringEft = ringEft;
}
