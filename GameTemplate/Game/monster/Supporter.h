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
	//�s���̃e�[�u�������o���B
	void MakeData();
};

