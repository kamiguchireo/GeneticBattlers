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
	m_status.MAXHP = hp;
	m_status.HP = m_status.MAXHP;
	m_status.MAXMP = mp;
	m_status.MP = m_status.MAXMP;
	m_status.ATK = atk;
	m_status.DEF = def;
	m_status.MAT = mat;
	m_status.MDF = mdf;
	m_status.DEX = dex;
}

void MonsterBase::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

bool MonsterBase::AddATB()
{
	//死亡時は処理を中断する。
	if (m_stateAI == en_state_Death) return true;

	m_activeTime += (float)m_status.DEX / 60.0f * 5;
	if (m_activeTime > 100.0f) {
		m_activeTime = 0.0f;
		return true;
	}
	return false;
}

void MonsterBase::SelectUseSkill(const std::vector<MonsterBase*>& list)
{
	if (m_useSkill != nullptr) return;

	SkillList* skillList = SkillList::GetInstance();

	//残りHPに応じて行動を決める。
	switch (m_stateAI)
	{
	case en_state_Good:
		m_useSkill = skillList->GetSkillData(0, 0);
		m_target = list[rand() % 3];
		break;

	case en_state_Usually:
		m_useSkill = skillList->GetSkillData(1, 0);
		m_target = list[rand() % 3];
		break;

	case en_state_Bad:
		m_useSkill = skillList->GetSkillData(4, 0);
		m_target = this;
		break;

	case en_state_Death:
		break;
	}
}

void MonsterBase::StateUpdate()
{
	//現在HP/最大HPの割合からステートを変化させる。
	float nowHP = (float)m_status.HP / (float)m_status.MAXHP;

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
	//残りHPに応じて行動を決める。
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
