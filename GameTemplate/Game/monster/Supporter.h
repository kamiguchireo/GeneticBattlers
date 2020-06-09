#pragma once
#include "MonsterBase.h"
class Supporter :public MonsterBase
{
public:
	Supporter();
	~Supporter();

	bool Start();
	void Update();
	//bool BattleAction();

private:
	const char* GetDefaultDataPath() 
	{
		return "Assets/AIData/SupporterDefault.bin";
	}
	//const char m_filePath[] = "Assets/AIData/SupporterDefault.bin";
};

