#pragma once
#include "Parabola.h"
class DamageFont :
	public Parabola
{
private:
	int m_damage;
	int m_fontSize;
public:
	DamageFont(int damage, Vector3 start);
	~DamageFont();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

};

