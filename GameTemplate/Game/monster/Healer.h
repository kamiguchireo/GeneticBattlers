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

private:
	//デフォルトの行動テーブルを作り出す。
	void MakeData()override;
};

