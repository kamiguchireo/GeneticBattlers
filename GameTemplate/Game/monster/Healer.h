#pragma once
#include "MonsterBase.h"
class Healer :public MonsterBase
{
public:
	Healer();
	~Healer();

	bool Start();

private:
	//const char* GetDefaultDataPath()
	//{
	//	return "Assets/AIData/DefaultData/HealerDefault.bin";
	//}
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/DefaultData/DataDefault.bin";
	}
	//const char m_filePath[] = "Assets/AIData/HealerDefault.bin";
};

