#pragma once
#include "MonsterBase.h"
class Supporter :public MonsterBase
{
public:
	Supporter();
	~Supporter();

	bool Start();

private:
	const char* GetDefaultDataPath() 
	{
		return "Assets/AIData/DefaultData/SupporterDefault.bin";
	}
	//const char m_filePath[] = "Assets/AIData/SupporterDefault.bin";
};

