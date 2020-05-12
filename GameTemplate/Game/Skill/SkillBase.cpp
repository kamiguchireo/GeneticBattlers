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

void SkillBase::InitSkill(const char * name, float power, float time, float acc, int no,bool isAttack, Elements ele, bool isMagic)
{
	SetSkillName(name);
	SetSkillPower(power);
	SetCoolTime(time);
	SetAccuracy(acc);
	SetSkillNo(no);
	SetIsAttack(isAttack);
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
	//�_���[�W�v�Z���s���B
	int damage = 0;
	int Attack, Defence;

	//���@�U�����ǂ����B
	if (!m_isMagic) {
		Attack = attack->GetStatusManager().GetStatus().ATK;
		Defence = target->GetStatusManager().GetStatus().DEF;
	}
	else {
		Attack = attack->GetStatusManager().GetStatus().MAT;
		Defence = target->GetStatusManager().GetStatus().MDF;
	}
	

	//���������B
	//float comp = GetCompatibility(m_skillElements, target->GetStatusManager().GetElements());
	float comp = 1.0f;

	//�_���[�W�v�Z���B
	damage = (int)((float)(Attack - Defence / 2) * skillPower * comp);
	//0�������Ȃ��悤�ɂ���B
	damage = max(damage, 0);

	if (accuracy * 100 < rand() % 101){
		damage = 0;
	}

	return damage;
}

