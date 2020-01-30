#include "stdafx.h"
#include "SkillBase.h"
#include "monster/MonsterBase.h"

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
	if (attack > en_elements_Num || attack < 0)
	{
		attack = max(0, min(en_elements_Num, attack));
	}
	if (target > en_elements_Num || target < 0)
	{
		target = max(0, min(en_elements_Num, target));
	}
	return m_elementsComp[attack][target];
}

int SkillBase::DamageCalcuration(MonsterBase * attack, MonsterBase * target)
{
	//�_���[�W�v�Z���s���B
	int damage = 0;
	int Attack, Defence;

	//���@�U�����ǂ����B
	if (!isMagic) {
		Attack = attack->GetStatus().ATK;
		Defence = target->GetStatus().DEF;
	}
	else {
		Attack = attack->GetStatus().MAT;
		Defence = target->GetStatus().MDF;
	}
	
	//MP���g���B
	if (!attack->UseMP(useMP)) {
		return 0;
	}
	//���������B
	float comp = GetCompatibility(m_skillElements, target->GetElements());

	//�_���[�W�v�Z���B
	damage = (int)((float)(Attack - Defence / 2) * skillPower * comp);

	return damage;
}

