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
	void SelectUseSkill(const std::vector<MonsterBase*>& enemylist, const std::vector<MonsterBase*>& allylist) override;
};

