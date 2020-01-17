#include "stdafx.h"
#include "SkillBase.h"

float SkillBase::eleCritical = 1.2f;
float SkillBase::eleResist = 0.8f;
float SkillBase::eleNormal = 1.0f;

SkillBase::SkillBase()
{
}


SkillBase::~SkillBase()
{
}

float SkillBase::GetCompatibility(int attack, int target)
{
	if (attack > 2 || attack < 0)
	{
		attack = max(0, min(2, attack));
	}
	if (target > 2 || target < 0)
	{
		target = max(0, min(2, target));
	}
	return m_elementsComp[attack][target];
}

