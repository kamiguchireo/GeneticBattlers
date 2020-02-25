#include "stdafx.h"
#include "Attacker.h"
#include "Skill/SkillList.h"

Attacker::Attacker()
{
}

Attacker::~Attacker()
{
}

bool Attacker::Start()
{
	m_model.Init(L"Assets/modelData/testModel.cmo");
	Draw();

	return true;
}

void Attacker::Update()
{
	Draw();
}

bool Attacker::BattleAction()
{
	MonsterBase* attack = this;

	bool flag = m_useSkill->UseSkill(attack, m_target);

	if (m_useSkill != nullptr && flag)
	{
		m_useSkill = nullptr;
		m_target = nullptr;
	}

	return flag;
}

void Attacker::SelectUseSkill(const std::vector<MonsterBase*>& list)
{
	//if (m_useSkill != nullptr) return;

	SkillList* skillList = SkillList::GetInstance();

	//int listSize = list.size();
	int res = rand() % 10;	//適当な乱数。

	//残りHPに応じて行動を決める。
	switch (m_stateAI)
	{
	case en_state_Good:
		if (res < 3) {
			m_useSkill = skillList->GetSkillData(0, 1);
		}
		else {
			m_useSkill = skillList->GetSkillData(0, 0);
		}
		m_target = list[rand() % list.size()];
		break;

	case en_state_Usually:
		if (res < 5) {
			m_useSkill = skillList->GetSkillData(0, 1);
		}
		else {
			m_useSkill = skillList->GetSkillData(0, 0);
		}
		m_target = list[rand() % list.size()];
		break;

	case en_state_Bad:
		m_useSkill = skillList->GetSkillData(0, 1);
		m_target = list[rand() % list.size()];
		break;

	case en_state_Death:
		break;
	}
}
