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


private:
	//デフォルトの行動テーブルを作り出す。
	void MakeData() override;
};

