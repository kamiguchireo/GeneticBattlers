#include "stdafx.h"
#include "MonsterBase.h"
#include "Skill/SkillList.h"


MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}

void MonsterBase::SetStatus(int hp, int mp, int atk, int def, int mat, int mdf, int dex)
{
	//��b�X�e�[�^�X��ݒ�B
	m_statusBase.HP = hp;
	m_statusBase.MP = mp;
	m_statusBase.ATK = atk;
	m_statusBase.DEF = def;
	m_statusBase.MAT = mat;
	m_statusBase.MDF = mdf;
	m_statusBase.DEX = dex;
	//�X�e�[�^�X�ɑ���B
	m_status = m_statusBase;
}

void MonsterBase::Draw()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	//�`�揈���B
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

bool MonsterBase::AddATB()
{
	//���S���͏����𒆒f����B
	if (m_stateAI == en_state_Death) return false;

	m_activeTime += (float)m_status.DEX / 144.0f;
	if (m_activeTime > m_coolTime) {
		m_activeTime = 0.0f;
		return true;
	}
	return false;
}

void MonsterBase::SelectUseSkill(const std::vector<MonsterBase*>& enemylist, const std::vector<MonsterBase*>& allylist)
{
	if (m_useSkill != nullptr) return;

	SkillList* skillList = SkillList::GetInstance();

	//�c��HP�ɉ����čs�������߂�B
	switch (m_stateAI)
	{
	case en_state_Good:
		m_useSkill = skillList->GetSkillData(0, 0);
		m_target = enemylist[rand() % enemylist.size()];
		break;

	case en_state_Usually:
		m_useSkill = skillList->GetSkillData(0, 1);
		m_target = enemylist[rand() % enemylist.size()];
		break;

	case en_state_Bad:
		m_useSkill = skillList->GetSkillData(1, 0);
		m_target = this;
		break;

	case en_state_Death:
		break;
	}
}

void MonsterBase::StateUpdate()
{
	//����HP/�ő�HP�̊�������X�e�[�g��ω�������B
	float nowHP = (float)m_status.HP / (float)m_statusBase.HP;

	if (2.0f / 3.0f < nowHP) {
		m_stateAI = en_state_Good;
	}
	else if (1.0f / 3.0f < nowHP
		&& 2.0f / 3.0f > nowHP) {
		m_stateAI = en_state_Usually;
	}
	else if (0 < m_status.HP
		&& 1.0f / 3.0f > nowHP) {
		m_stateAI = en_state_Bad;
	}
	else { 
		m_stateAI = en_state_Death; 
		m_activeTime = 0.0f;
	}
}

bool MonsterBase::Action()
{
	bool flag = false;
	//�c��HP�ɉ����čs�������߂�B
	switch (m_stateAI)
	{
	case en_state_Good:
		flag = Action_good();
		break;
	
	case en_state_Usually:
		flag = Action_usually();
		break;
	
	case en_state_Bad:
		flag = Action_bad();
		break;
	
	case en_state_Death:
		return true;
		break;
	}
	return flag;
}
