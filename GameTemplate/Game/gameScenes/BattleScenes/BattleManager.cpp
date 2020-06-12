#include "stdafx.h"
#include "BattleManager.h"
#include "monster/MonsterBase.h"

BattleManager::BattleManager()
{
}

BattleManager::~BattleManager()
{
	for (auto p : m_monsterTeam) {
		DeleteGO(p);
	}
	for (auto p : m_monsterEnemy) {
		DeleteGO(p);
	}
}

void BattleManager::BattleUpdate()
{
	switch (m_battleState)
	{
	case enState_ATB:
		ActiveTimeUpdate();
		break;
	case enState_ACT:
		MonsterAction();
		break;
	case enState_Scoring:
		MonsterScoring();
		break;
	}
}

void BattleManager::SetTeams()
{
	for (auto p : m_monsterTeam) {
		p->SetTeamMenber(m_monsterTeam);
	}
	for (auto p : m_monsterEnemy) {
		p->SetTeamMenber(m_monsterEnemy);
	}
}

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
			m_monsterACTList.push_back({ m_monsterTeam[i], false });
			//�X�e�[�g��ύX�B
			m_battleState = enState_ACT;
		}
	}
	for (int i = 0; i < m_monsterEnemy.size(); i++)
	{
		bool is_action = m_monsterEnemy[i]->AddATB();

		//�Q�[�W�����܂�؂�����|�C���^���擾����B�@
		if (is_action) {
			m_monsterACTList.push_back({ m_monsterEnemy[i], true });
			//�X�e�[�g��ύX�B
			m_battleState = enState_ACT;
		}
	}
}

void BattleManager::MonsterAction()
{
	if (m_usingSkill == nullptr) {
		m_monsterACT = m_monsterACTList.front();
		SortTeams();

		int skill, target;
		//�s���̌���B
		if (m_monsterACT.isEnemy) {		//�G�̍s���I���B
			m_monsterACT.actMonster->SelectUseSkill(m_monsterTeam,m_monsterEnemy, skill,target);
		}
		else {							//�����̍s���I���B
			m_monsterACT.actMonster->SelectUseSkill(m_monsterEnemy,m_monsterTeam, skill, target);
		}
		//�X�L���̎擾�B
		int skillTable = (int)(skill / 100);
		int No = skill % 100;
		m_usingSkill = SkillList::GetInstance()->GetSkillData(skillTable, No);
		//�g�p�ҁA�^�[�Q�b�g�̐ݒ�B
		m_usingSkill->SetUser(m_monsterACT.actMonster);
		if (m_monsterACT.isEnemy) {
			if (m_usingSkill->IsAttack()) {
				m_usingSkill->SetTarget(m_monsterTeam[target]);
			}
			else {
				m_usingSkill->SetTarget(m_monsterEnemy[target]);
			}
		}
		else {
			if (m_usingSkill->IsAttack()) {
				m_usingSkill->SetTarget(m_monsterEnemy[target]);
			}
			else {
				m_usingSkill->SetTarget(m_monsterTeam[target]);
			}
		}
	}
	//�s�����I�������X�e�[�g�؂�ւ��B
	if (m_usingSkill->IsDead()) {
		//�S���̃^�C���Q�[�W�����Z���Ă����B
		for (int i = 0; i < m_monsterTeam.size(); i++)
		{
			m_monsterTeam[i]->StateUpdate();
		}
		for (int i = 0; i < m_monsterEnemy.size(); i++)
		{
			m_monsterEnemy[i]->StateUpdate();
		}
		m_battleState = enState_Scoring;
		m_usingSkill = nullptr;
	}
}

void BattleManager::MonsterScoring()
{
	bool flag = m_monsterACT.actMonster->ACTScoring();

	if (flag) {
		//�s�����I�������|�C���^��null������B
		m_monsterACTList.erase(m_monsterACTList.begin());
		m_monsterACT = { nullptr,false };		//�������B


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

void BattleManager::SortTeams()
{
	//����HP�̒Ⴂ�����珇�ԂɃ\�[�g�B
	//����퓬�̏����̂ق��ł�����ق��������C������Ȃ�
	for (int i = 0; i < m_monsterTeam.size(); i++) {
		for (int j = i; j < m_monsterTeam.size(); j++) {
			if (m_monsterTeam[i]->GetStatusManager().GetStatus().HP > m_monsterTeam[j]->GetStatusManager().GetStatus().HP) {
				auto hoge = m_monsterTeam[i];
				m_monsterTeam[i] = m_monsterTeam[j];
				m_monsterTeam[j] = hoge;
			}
		}
	}
	for (int i = 0; i < m_monsterEnemy.size(); i++) {
		for (int j = i; j < m_monsterEnemy.size(); j++) {
			if (m_monsterEnemy[i]->GetStatusManager().GetStatus().HP > m_monsterEnemy[j]->GetStatusManager().GetStatus().HP) {
				auto hoge = m_monsterEnemy[i];
				m_monsterEnemy[i] = m_monsterEnemy[j];
				m_monsterEnemy[j] = hoge;
			}
		}
	}
	//HP��0�̂�͌��ɉ񂷁B
	for (int i = m_monsterTeam.size() - 1; i >= 0; i--) {
		for (int j = i; j < m_monsterTeam.size(); j++) {
			if (m_monsterTeam[i]->GetStatusManager().GetStatus().HP <= 0) {
				auto hoge = m_monsterTeam[i];
				m_monsterTeam[i] = m_monsterTeam[j];
				m_monsterTeam[j] = hoge;
			}
		}
	}
	for (int i = m_monsterEnemy.size() - 1; i >= 0; i--) {
		for (int j = i; j < m_monsterEnemy.size(); j++) {
			if (m_monsterEnemy[i]->GetStatusManager().GetStatus().HP <= 0) {
				auto hoge = m_monsterEnemy[i];
				m_monsterEnemy[i] = m_monsterEnemy[j];
				m_monsterEnemy[j] = hoge;
			}
		}
	}
}
