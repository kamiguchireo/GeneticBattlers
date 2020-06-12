#pragma once
#include "Skill/SkillList.h"

struct ACTMonsterInfo {
	MonsterBase* actMonster = nullptr;
	bool isEnemy = false;
};

class BattleManager
{
public:
	BattleManager();
	~BattleManager();

	//�퓬�����B
	void BattleUpdate();
	//�����̃`�[�����Z�b�g�B
	void PushBackTeams(MonsterBase* monster)
	{
		m_monsterTeam.push_back(monster);
	}
	//�G�̃`�[�����Z�b�g�B
	void PushBackEnemys(MonsterBase* enemy)
	{
		m_monsterEnemy.push_back(enemy);
	}
	void SetTeams();

private:
	typedef std::vector<MonsterBase*> MonsterList;

	/// <summary>
	/// �A�N�e�B�u�^�C���̉��Z�B
	/// </summary>
	void ActiveTimeUpdate();
	/// <summary>
	/// �s��������B
	/// </summary>
	void MonsterAction();
	/// <summary>
	/// �]��������B
	/// </summary>
	void MonsterScoring();
	//HP�Ń\�[�g���s���B
	void SortTeams();

	//�o�g���̏����؂�ւ�
	enum BattleState {
		enState_ATB,
		enState_ACT,
		enState_Scoring
	};
	//�����X�^�[�̃|�C���^�B
	MonsterList m_monsterTeam;
	MonsterList m_monsterEnemy;
	std::vector <ACTMonsterInfo> m_monsterACTList;	//!<�s�����̃��X�g�B
	ACTMonsterInfo m_monsterACT;					//!<���ݍs�����̃����X�^�[�B
	SkillList skillList;							//!<�X�L�����X�g�B
	SkillBase* m_usingSkill = nullptr;				//���ݎg�p���̃X�L���B
	BattleState m_battleState = enState_ATB;
};

