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
	//�f�t�H���g�̍s���e�[�u�������o���B
	void MakeData()override;
};

