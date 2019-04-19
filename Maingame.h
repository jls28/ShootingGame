#pragma once
class Maingame
{
public:
	Maingame();
	virtual ~Maingame();

	void Init();
	void Update();
	void Render();
	void Destroy();

	void ResetDevice();
	void LostDevice();
};

