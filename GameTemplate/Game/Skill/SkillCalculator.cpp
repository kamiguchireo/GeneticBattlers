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
	//�X�L�����擾�B
	SkillData skillInfo = m_skillData->GetSkillData(SkillNo);
	int res = 0;	//���ʒl�B
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
	//�N�[���^�C���̐ݒ�B
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

	//�g�p�\�B���ł�MP����B
	if (user->UseMP(skillInfo.useMP))
	{
		return true;
	}

	//MP������Ȃ��B
	return false;
}

int SkillCalculator::AttackCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//�_���[�W�v�Z���s���B
	int damage = 0;

	int Attack = user->GetStatus().ATK;
	int Defence = target->GetStatus().DEF;

	//�_���[�W�v�Z���B
	damage = (int)((float)(Attack - Defence / 2) * skill.Power);
	//0�������Ȃ��悤�ɂ���B
	damage = max(damage, 0);

	if (skill.HitRate * 100 < g_random.GetRandomInt() % 100 + 1) {
		damage = 0;
	}
	else
	{
		//�������Ȃ������B
		damage = target->Damage(damage);
	}

	return damage;
}

int SkillCalculator::HealCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//�񕜗ʂ̌v�Z�B
	int res = static_cast<int>(user->GetStatus().HEAL * skill.Power);
	res = target->Healing(res);
	return res;
}

int SkillCalculator::BuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//�o�t�̌��ʎ��ԁB
	float Time = BUFF_TIME + static_cast<float>(user->GetStatus().BUF) * (3.0f);
	int res = target->Monster_Buff(skill.StatusChange, skill.Power, Time);
	return res;
}

int SkillCalculator::DebuffCalculation(CStatusBase* user, CStatusBase* target, SkillData& skill)
{
	//�f�o�t�̌��ʎ��ԁB
	float Time = BUFF_TIME + static_cast<float>(user->GetStatus().BUF) * (3.0f);
	int res = target->Monster_Debuff(skill.StatusChange, skill.Power, Time);
	return res;
}

