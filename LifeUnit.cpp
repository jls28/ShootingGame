#include "DXUT.h"
#include "LifeUnit.h"

#include "GageBar.h"

void LifeUnit::UseHpBar(const string & hpbarName, float offsetX, float offsetY)
{
	if (!gageBar)
		gageBar = Instantiate(GageBar(hpbarName, m_position, maxHp, curHp, Vector3(offsetX, offsetY, 0)));
}

void LifeUnit::DelHpBar()
{
	SAFE_KILL(gageBar);
}


void LifeUnit::SetFrameAsRotation(float rot, float frameChangeSpeed)
{
	if (0.f < rot && rot <= 22.5f && !(m_frame.nowFrame >= 60 && m_frame.nowFrame <= 69))
		UseFrame(60, 69, frameChangeSpeed);
	else if (22.5f < rot && rot <= 67.5f && !(m_frame.nowFrame >= 70 && m_frame.nowFrame <= 79))
		UseFrame(70, 79, frameChangeSpeed);
	else if (67.5f < rot && rot <= 112.5f && !(m_frame.nowFrame >= 0 && m_frame.nowFrame <= 9))
		UseFrame(0, 9, frameChangeSpeed);
	else if (112.5f < rot && rot <= 157.5f && !(m_frame.nowFrame >= 10 && m_frame.nowFrame <= 19))
		UseFrame(10, 19, frameChangeSpeed);
	else if (157.5f < rot && rot <= 180.f && !(m_frame.nowFrame >= 20 && m_frame.nowFrame <= 29))
		UseFrame(20, 29, frameChangeSpeed);
	else if (-180 < rot && rot <= -157.5f && !(m_frame.nowFrame >= 20 && m_frame.nowFrame <= 29))
		UseFrame(20, 29, frameChangeSpeed);
	else if (-157.5f < rot && rot <= -112.5f && !(m_frame.nowFrame >= 30 && m_frame.nowFrame <= 39))
		UseFrame(30, 39, frameChangeSpeed);
	else if (-112.5f < rot && rot <= -67.5f && !(m_frame.nowFrame >= 40 && m_frame.nowFrame <= 49))
		UseFrame(40, 49, frameChangeSpeed);
	else if (-67.5f < rot && rot <= -22.5f && !(m_frame.nowFrame >= 50 && m_frame.nowFrame <= 59))
		UseFrame(50, 59, frameChangeSpeed);
	else if (-22.5f < rot && rot <= 0.f && !(m_frame.nowFrame >= 60 && m_frame.nowFrame <= 69))
		UseFrame(60, 69, frameChangeSpeed);
}
