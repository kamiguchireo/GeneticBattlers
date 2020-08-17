#pragma once
#include "Skill/SkillList.h"

class BattleScenes;

struct ACTMonsterInfo {
	MonsterBase* actMonster = nullptr;
	bool isEnemy = false;
};

namespace job {
	enum JOB {
		enjob_Attacker,
		enjob_Healer,
		enjob_Supotter,
		enjob_Num
	};
}

class BattleManager:public IGameObject
{
public:
	BattleManager();
	~BattleManager();

	bool Start();
	void Update();

	//�����̃`�[�����Z�b�g�B
	void PushBackTeams(MonsterBase* monster, job::JOB j)
	{
		m_monsterTeam[j] = monster;
	}
	//�G�̃`�[�����Z�b�g�B
	void PushBackEnemys(MonsterBase* enemy, job::JOB j)
	{
		m_monsterEnemy[j] = enemy;
	}
	//���ꂼ��ɖ����`�[����m�点��B
	void SetTeams();
	/// <summary>
	/// �o�g���V�[���̃|�C���^�ݒ�B
	/// </summary>
	/// <param name="p">�|�C���^�B</param>
	void SetScenePointa(BattleScenes* p)
	{
		m_scenes = p;
	}
	//GI�̍X�V�����ƕۑ���������B
	void SaveData()
	{
		//�S�����̋L�^���s���B
		for (auto p : m_monsterTeam) {
			auto GI = p->GetAIManager();
			GI.Save();
		}
	}
	void SetIsBattle(bool flag)
	{
		m_isBattle = flag;
	}

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
	////HP�Ń\�[�g���s���B
	//void SortTeams();

	//�o�g���̏����؂�ւ�
	enum BattleState {
		enState_ATB,
		enState_ACT,
		enState_Scoring
	};
	BattleScenes* m_scenes = nullptr;
	//�����X�^�[�̃|�C���^�B
	MonsterList m_monsterTeam;
	MonsterList m_monsterEnemy;
	std::vector <ACTMonsterInfo> m_monsterACTList;	//!<�s�����̃��X�g�B
	ACTMonsterInfo m_monsterACT;					//!<���ݍs�����̃����X�^�[�B
	SkillList skillList;							//!<�X�L�����X�g�B
	SkillBase* m_usingSkill = nullptr;				//���ݎg�p���̃X�L���B
	BattleState m_battleState = enState_ATB;
	bool m_isBattle = false;
};

