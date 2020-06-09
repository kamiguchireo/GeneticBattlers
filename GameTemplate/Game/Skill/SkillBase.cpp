#include "stdafx.h"
#include "SkillBase.h"

SkillBase::SkillBase()
{
}


SkillBase::~SkillBase()
{
}

void SkillBase::InitSkill(const char * name, float power, float time, float acc, int no)
{
	SetSkillName(name);
	SetSkillPower(power);
	SetCoolTime(time);
	SetAccuracy(acc);
	SetSkillNo(no);
}

int SkillBase::DamageCalcuration()
{
	//ダメージ計算を行う。
	int damage = 0;
	int Attack, Defence;

	//魔法攻撃かどうか。
	if (!IsMagic()) {
		Attack = m_user->GetStatusManager().GetStatus().ATK;
		Defence = m_target->GetStatusManager().GetStatus().DEF;
	}
	else {
		Attack = m_user->GetStatusManager().GetStatus().MAT;
		Defence = m_target->GetStatusManager().GetStatus().MDF;
	}
	
	//ダメージ計算式。
	damage = (int)((float)(Attack - Defence / 2) * skillPower);
	//0を下回らないようにする。
	damage = max(damage, 0);

	if (accuracy * 100 < rand() % 101){
		damage = 0;
	}

	return damage;
}

