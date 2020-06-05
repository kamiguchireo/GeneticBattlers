#pragma once
#include "Skill/SkillList.h"


class BattleManager
{
public:
	BattleManager() {};
	~BattleManager() {};

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

	//�o�g���̏����؂�ւ�
	enum BattleState {
		enState_ATB,
		enState_ACT,
		enState_Scoring
	};
	//�����X�^�[�̃|�C���^�B
	MonsterList m_monsterTeam;
	MonsterList m_monsterEnemy;
	MonsterList m_monsterACTList;	//!<�s�����̃��X�g�B
	MonsterBase* m_monsterACT = nullptr;	//!<���ݍs�����̃����X�^�[�B
	SkillList skillList;					//!<�X�L�����X�g�B
	BattleState m_battleState = enState_ATB;
};

