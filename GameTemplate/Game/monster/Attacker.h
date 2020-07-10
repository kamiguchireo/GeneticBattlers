#pragma once
#include "MonsterBase.h"
class Attacker :public MonsterBase
{
public:
	Attacker();
	~Attacker();

	bool Start();

private:
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/DefaultData/AttackerDefault.bin";
	}
	//const char m_filePath[] = "Assets/AIData/AttackerDefault.bin";
};

