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
	//�f�t�H���g�̍s���e�[�u�������o���B
	void MakeData() override;
};

