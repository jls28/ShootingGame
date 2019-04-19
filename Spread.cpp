#include "DXUT.h"
#include "Spread.h"

#include "NormalBullet.h"

Spread::Spread(GameObject * owner, Vector3 position)
{
	m_owner = owner;
	SetPosition(position);
}

Spread::~Spread()
{
}

void Spread::Init()
{
	GunSetting(500, 3000, 12, 80, 0);
	SetTag("SPREAD");
	SetCenter(Vector3(0, 0, 0));
	m_bulletSpeed = 750;
}

void Spread::Update()
{
	Gun::Update();
}

void Spread::Render()
{
	DrawInfo("SPREAD");
}

void Spread::Destroy()
{
}

void Spread::OnCollision(Collider * col)
{
}

void Spread::Fire(Vector3 destination, int key)
{
	if (AutoGeneric(destination, key)) {

		CAMERA.distanceShake(position, 50, 4);

		/*
		for (int i = 0; i < 15; i++) {
			Vector3 d = GetDirection(m_rebound, destination);
			Instantiate(NormalBullet(m_owner->tag, p, d, 750, 25))->TextureSet("SPREAD_BULLET", "SPREAD_EFT");
		}*/
		SOUND.DuplicateDistancePlay("SPREAD", position, 100);

		FireNWayBullet(6, GetDirection(m_rebound, destination), 6);
	}
}

void Spread::FireNWayBullet(float theta, Vector3 pivotVec, int n)
{
	// 탄과 탄 사이의 각도를 라디안으로 변환하기
	float rad_step = D3DXToRadian(theta);

	// 가장자리의 탄과 중심 부분의 탄의 각도를 계산하기
	float rad = n % 2 ? -n / 2 * rad_step : (-n / 2 + 0.5) * rad_step;

	// n개의 탄의 속도를 계산하기
	for (int i = 0; i < n; i++, rad += rad_step) {
		
		Vector3 d;

		float c = cos(rad), s = sin(rad);
		d.x = pivotVec.x * c - pivotVec.y * s;
		d.y = pivotVec.x * s + pivotVec.y * c;
		d.z = 0;

		D3DXVec3Normalize(&d, &d);

		Vector3 p = GetFirePos(GetRotation(d));
		//Vector3 p = position;

		auto bullet = Instantiate(NormalBullet(m_owner->tag, p, d, m_bulletSpeed, 25));
		bullet->TextureSet(bulletEft, ringEft);

		if (m_owner->tag == "PLAYER") {
			bullet->CollideSet("BLUE_W_EFT", "BLUE_T_EFT");
		}
		else if (m_owner->tag == "ENEMY")
		{
			bullet->CollideSet("RED_W_EFT", "RED_T_EFT");
		}
	}
}
