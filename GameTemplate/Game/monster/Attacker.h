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
	////�X�L���I���B
	//void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team) override;

	//AI�f�[�^��ǂݍ��݂����B
	void Init(const char* filePath);
	//AI�f�[�^���������݂����B
	virtual void Save(const char* filePath);

private:
};

