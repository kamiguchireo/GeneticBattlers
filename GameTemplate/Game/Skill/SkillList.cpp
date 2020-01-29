#include "stdafx.h"
#include "SkillList.h"
#include "monster/MonsterBase.h"

SkillList*SkillList::m_instance = nullptr;

SkillList::SkillList()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}

	m_instance = this;

	//�ʏ�s���B
	const int typeNum = 5;
	SkillTable typeList[typeNum];
	typeList[0].push_back(NewGO<Attack>(0));
	typeList[0].push_back(NewGO<Rest>(0));

	//�����@�B
	typeList[1].push_back(NewGO<Fire>(0));

	//�񕜖��@�A�o�t���@�B
	typeList[4].push_back(NewGO<Heal>(0));

	for (int i = 0; i < typeNum; i++)
	{
		m_skillList.push_back(typeList[i]);
	}
}

SkillList::~SkillList()
{
	for (SkillTable table : m_skillList)
	{
		for (SkillBase* SB : table)
		{
			DeleteGO(SB);
		}
	}

	m_instance = nullptr;
}

//�ʏ�U���B
bool Attack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	//attack->UseMP(useMP);

	int damage = DamageCalcuration(attack, target);

	attack->Damage(damage);

	return false;
}

//�x�e�B
bool Rest::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	int result = attack->GetStatus().MAXMP * skillPower;

	attack->HealingMP(result);

	return false;
}

//�t�@�C�A�B
bool Fire::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	int damage = DamageCalcuration(attack, target);

	attack->Damage(damage);

	return false;
}

//�q�[���B
bool Heal::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	int result = attack->GetStatus().MAT * skillPower;

	target->Healing(result);

	return false;
}
