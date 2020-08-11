#include "stdafx.h"
#include "SkillCalculator.h"
#include "SkillDataLoad.h"
#include "monster/parameter/StatusBase.h"

SkillCalculator::SkillCalculator()
{
}

SkillCalculator::~SkillCalculator()
{
}

int SkillCalculator::SkillCalculation(Status & user, Status & target, int SkillNo)
{
	int res = 0;	//å¯â ílÅB
	int type = static_cast<int>(SkillNo / 100);
	switch (type)
	{
	case en_Attack:
		res = AttackCalculation(user, target, SkillNo);
		break;
	case en_Heal:
		res = HealCalculation(user, target, SkillNo);
		break;
	case en_Buff:
		res = BuffCalculation(user, target, SkillNo);
		break;
	case en_Debuff:
		res = DebuffCalculation(user, target, SkillNo);
		break;
	default:
		break;
	}
	return res;
}

int SkillCalculator::SkillCalculation(Status & user, std::vector<Status&> targets, int SkillNo)
{
	int res = 0;

	for (int i = 0; i < targets.size(); i++)
	{
		res += SkillCalculation(user, targets[i], SkillNo);
	}

	return res;
}

int SkillCalculator::AttackCalculation(Status & user, Status & target, int SkillNo)
{
	return 0;
}

int SkillCalculator::HealCalculation(Status & user, Status & target, int SkillNo)
{
	return 0;
}

int SkillCalculator::BuffCalculation(Status & user, Status & target, int SkillNo)
{
	return 0;
}

int SkillCalculator::DebuffCalculation(Status & user, Status & target, int SkillNo)
{
	return 0;
}

