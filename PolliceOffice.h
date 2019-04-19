#pragma once
#include "GameObject.h"


class Button;
class Trigger;
class Player;
class PolliceOffice :
	public GameObject
{
private:
	Button* buttons[4];
	Trigger* range;

	Player* player;
public:
	PolliceOffice(Trigger* trigger);
	virtual ~PolliceOffice();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

public:
	static bool IsSpawn;

	void DeleteButtons();
};