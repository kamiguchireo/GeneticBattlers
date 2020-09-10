#pragma once
#include "MonsterBase.h"
class Healer :public MonsterBase
{
public:
	Healer();
	~Healer();

	bool Start();

private:
	const char* GetDefaultDataPath()
	{
		return "Assets/AIData/DefaultData/DataDefault.bin";
	}
};

