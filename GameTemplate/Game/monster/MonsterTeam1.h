#pragma once
#include "monster/MonsterBase.h"
class MonsterTeam1 : public MonsterBase
{
public:
	MonsterTeam1();
	~MonsterTeam1();
	bool Start();
	void Update();
};

