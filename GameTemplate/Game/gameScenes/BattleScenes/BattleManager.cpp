#include "stdafx.h"
#include "BattleManager.h"
#include "monster/MonsterBase.h"

void BattleManager::ActiveTimeUpdate()
{
	//�s�����Ȃ璆�f�B
	if (m_monsterACTList.size() != 0)return;

	//�S���̃^�C���Q�[�W�����Z���Ă����B
	for (int i = 0; i < m_monsterTeam.size(); i++)
	{
		bool is_action = m_monsterTeam[i]->AddATB();

		//�Q�[�W�����܂�؂�����|�C���^���擾����B�@
		if (is_action) {
			m_monsterACTList.push_back(m_monsterEnemy[i]);
			m_monsterTeam[i]->SelectUseSkill(m_monsterEnemy, m_monsterTeam);
			//�X�e�[�g��ύX�B
			m_battleState = enState_ACT;
		}
	}
	for (int i = 0; i < m_monsterEnemy.size(); i++)
	{
		bool is_action = m_monsterEnemy[i]->AddATB();

		//�Q�[�W�����܂�؂�����|�C���^���擾����B�@
		if (is_action) {
			m_monsterACTList.push_back(m_monsterEnemy[i]);
			m_monsterEnemy[i]->SelectUseSkill(m_monsterTeam, m_monsterEnemy);
			//�X�e�[�g��ύX�B
			m_battleState = enState_ACT;
		}
	}
}

void BattleManager::MonsterAction()
{
	m_monsterACT = m_monsterACTList.front();

	//�s�����I���܂ōs����������B
	bool is_playAction = m_monsterACT->BattleAction();

	if (is_playAction) {
		//�c��HP�ɉ����ăX�e�[�g���X�V�B
		for (int i = 0; i < m_monsterTeam.size(); i++) {
			m_monsterTeam[i]->StateUpdate();
		}
		for (int i = 0; i < m_monsterEnemy.size(); i++) {
			m_monsterEnemy[i]->StateUpdate();
		}

		m_battleState = enState_Scoring;
	}
}

void BattleManager::MonsterScoring()
{
	bool flag = m_monsterACT->ACTScoring();

	if (flag) {
		//�s�����I�������|�C���^��null������B
		m_monsterACTList.erase(m_monsterACTList.begin());
		m_monsterACT = nullptr;


		int myDeath = 0;
		int eneDeath = 0;

		//�f�X�����J�E���g����B
		for (int i = 0; i < m_monsterTeam.size(); i++) {
			if (m_monsterTeam[i]->IsDeath())myDeath++;
		}
		for (int i = 0; i < m_monsterEnemy.size(); i++) {
			if (m_monsterEnemy[i]->IsDeath())eneDeath++;
		}
		//�ǂ��炩���S�ł���΃��U���g��
		if (myDeath == m_monsterTeam.size()) {
			//�o�g���V�[���ɑ΂��ăX�e�[�g�̕ω��Ə��s�����n��
			return;
		}
		else if (eneDeath == m_monsterEnemy.size()) {
			return;
		}

		//�N���s�����Ă��Ȃ��Ȃ�
		if (m_monsterACTList.size() == 0) {
			m_battleState = enState_ATB;
		}
		else {
			m_battleState = enState_ACT;
		}

	}
}
