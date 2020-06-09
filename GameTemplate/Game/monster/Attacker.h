#pragma once
#include "MonsterBase.h"
class Attacker :public MonsterBase
{
public:
	Attacker();
	~Attacker();

	bool Start();
	void Update();
	//bool BattleAction();


private:
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/AttackerDefault.bin";
	}
	//const char m_filePath[] = "Assets/AIData/AttackerDefault.bin";
};

