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
	////�X�L���I���B
	//void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team) override;

	//AI�f�[�^��ǂݍ��݂����B
	void Init(const char* filePath);
	//AI�f�[�^���������݂����B
	virtual void Save(const char* filePath);
};

