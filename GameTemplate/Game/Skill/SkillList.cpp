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

	//通常行動。
	const int typeNum = 5;
	SkillTable typeList[typeNum];
	typeList[0].push_back(NewGO<Attack>(0));
	typeList[0].push_back(NewGO<Rest>(0));

	//炎魔法。
	typeList[1].push_back(NewGO<Fire>(0));

	//回復魔法、バフ魔法。
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

//通常攻撃。
bool Attack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	//attack->UseMP(useMP);

	int damage = DamageCalcuration(attack, target);

	attack->Damage(damage);

	return false;
}

//休憩。
bool Rest::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	int result = attack->GetStatus().MAXMP * skillPower;

	attack->HealingMP(result);

	return false;
}

//ファイア。
bool Fire::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	int damage = DamageCalcuration(attack, target);

	attack->Damage(damage);

	return false;
}

//ヒール。
bool Heal::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	int result = attack->GetStatus().MAT * skillPower;

	target->Healing(result);

	return false;
}
