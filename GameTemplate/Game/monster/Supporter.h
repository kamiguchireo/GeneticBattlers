#pragma once
#include "MonsterBase.h"
class Supporter :public MonsterBase
{
public:
	Supporter();
	~Supporter();

	bool Start();
	void Update();
	bool BattleAction();

private:
	//行動のテーブルを作り出す。
	void MakeData();
};

