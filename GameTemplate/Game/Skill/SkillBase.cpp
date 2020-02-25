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

void SkillBase::InitSkill(const char * name, float power, float time, float acc, int no, Elements ele, bool isMagic)
{
	SetSkillName(name);
	SetSkillPower(power);
	SetCoolTime(time);
	SetAccuracy(acc);
	SetSkillNo(no);
	SetElements(ele);
	SetMagic(isMagic);
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
	//ダメージ計算を行う。
	int damage = 0;
	int Attack, Defence;

	//魔法攻撃かどうか。
	if (!m_isMagic) {
		Attack = attack->GetStatus().ATK;
		Defence = target->GetStatus().DEF;
	}
	else {
		Attack = attack->GetStatus().MAT;
		Defence = target->GetStatus().MDF;
	}
	

	//属性相性。
	float comp = GetCompatibility(m_skillElements, target->GetElements());

	//ダメージ計算式。
	damage = (int)((float)(Attack - Defence / 2) * skillPower * comp);

	if (accuracy * 100 < rand() % 101){
		damage = 0;
	}

	return damage;
}

