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
	//�X�L���I���B
	void SelectUseSkill(const std::vector<MonsterBase*>& e_team, const std::vector<MonsterBase*>& m_team) override;
	//AI�f�[�^��ǂݍ��݂����B
	void Init(const wchar_t* filePath);
};

