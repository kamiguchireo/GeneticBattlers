#include "stdafx.h"
#include "SkillList.h"
#include "monster/MonsterBase.h"


SkillList::SkillList()
{
}


SkillList::~SkillList()
{
}

bool Attack::UseSkill(MonsterBase * attack, MonsterBase * target)
{
	attack->UseMP(useMP);

	int damage = DamageCalcuration(attack, target);

	attack->Damage(damage);

	return false;
}
