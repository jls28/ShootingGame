#pragma once
#include "Singleton.h"
class DataManager :
	public Singleton<DataManager>
{
private:
	int gold = 0;
public:
	DataManager();
	virtual ~DataManager();

	int GetGold() { return gold; }
	void SetGold(int g) { gold = g; }
	void AddGold(int g) { gold += g; }
};

#define DATA (*DataManager::Instance())