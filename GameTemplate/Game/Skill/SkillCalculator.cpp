#include "stdafx.h"
#include "SkillCalculator.h"
#include "SkillDataLoad.h"
#include "monster/parameter/StatusBase.h"

SkillCalculator::SkillCalculator()
{
	m_skillData = SkillDataLoad::GetInstance();
}

SkillCalculator::~SkillCalculator()
{
}

int SkillCalculator::SkillCalculation(CStatusBase* user, CStatusBase* target, int SkillNo)
{
	//スキル情報取得。
	SkillData skillInfo = m_skillData->GetSkillData(SkillNo);
	int res = 0;	//効果値。
	int type = static_cast<int>(SkillNo / 100);
	switch (type)
	{
	case en_Attack:
		res = AttackCalculation(user, target, skillInfo);
		break;
	case en_Heal:
		res = HealCalculation(user, target, skillInfo);
		break;
	case en_Buff:
		res = BuffCalculation(user, target, skillInfo);
		break;
	case en_Debuff:
		res = DebuffCalculation(user, target, skillInfo);
		break;
	default:
		break;
	}
	//クールタイムの設定。
	user->SetCoolTime(skillInfo.CoolTime);
	return res;
}

int SkillCalculator::SkillCalculation(CStatusBase* user, std::vector<CStatusBase*> targets, int SkillNo)
{
	int res = 0;

	for (int i = 0; i < targets.size(); i++)
	{
		res += SkillCalculation(user, targets[i], SkillNo);
	}

	return res;
}

bool SkillCalculator::IsAvailableSkill(CStatusBase * user, const int SkillNo)
{
	SkillData skillInfo = m_skillData->GetSkillData(SkillNo);

	//使用可能。ついでにMP消費。
	if (user->UseMP(skillInfo.useMP))
	{
		return true;
	}

	//MPが足りない。
	return false;
}

int SkillCalculator::AttackCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//ダメージ計算を行う。
	int damage = 0;

	int Attack = user->GetStatus().ATK;
	int Defence = target->GetStatus().DEF;

	//ダメージ計算式。
	damage = (int)((float)(Attack - Defence / 2) * skill.Power);
	//0を下回らないようにする。
	damage = max(damage, 0);

	if (skill.HitRate * 100 < g_random.GetRandomInt() % 100 + 1) {
		damage = 0;
	}
	else
	{
		//回避されなかった。
		damage = target->Damage(damage);
	}

	return damage;
}

int SkillCalculator::HealCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//回復量の計算。
	int res = static_cast<int>(user->GetStatus().HEAL * skill.Power);
	res = target->Healing(res);
	return res;
}

int SkillCalculator::BuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//バフの効果時間。
	float Time = BUFF_TIME + static_cast<float>(user->GetStatus().BUF) * (3.0f);
	int res = target->Monster_Buff(skill.StatusChange, skill.Power, Time);
	return res;
}

int SkillCalculator::DebuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//デバフの効果時間。
	float Time = BUFF_TIME + static_cast<float>(user->GetStatus().BUF) * (3.0f);
	int res = target->Monster_Debuff(skill.StatusChange, skill.Power, Time);
	return res;
}

