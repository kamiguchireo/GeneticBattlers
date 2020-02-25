#pragma once
#include "MonsterBase.h"
class Attacker :public MonsterBase
{
public:
	Attacker();
	~Attacker();

	bool Start();
	void Update();
	bool BattleAction();
	void SelectUseSkill(const std::vector<MonsterBase*>& list) override;
};

