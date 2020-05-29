#pragma once
#include "MonsterBase.h"
class Healer :public MonsterBase
{
public:
	Healer();
	~Healer();

	bool Start();
	void Update();
	bool BattleAction();

private:
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/HealerDefault.bin";
	}
	//const char m_filePath[] = "Assets/AIData/HealerDefault.bin";
};

