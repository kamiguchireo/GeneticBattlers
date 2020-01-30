#pragma once
#include "Skill/SkillList.h"

class MonsterBase;
class MonsterTeam1;
//class SkillList;

class BattleScenes : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	BattleScenes();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~BattleScenes();

	bool Start();
	void Update();

	void InitMonster();
	void MonsterAction();

private:
	void ActiveTimeUpdate();
	std::vector<MonsterBase*>m_monsterTeam1List;
	std::vector<MonsterBase*>m_monsterTeam2List;
	MonsterBase* m_monsterACT = nullptr;
	SkillList skillList;
};

