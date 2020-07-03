#include "stdafx.h"
#include "SkillBase.h"
#include "SkillLog.h"

SkillBase::SkillBase()
{
}


SkillBase::~SkillBase()
{
	//�ҋ@��Ԃ̃A�j���[�V�����̍Đ��B
	//m_user->AnimationIdle();
}

bool SkillBase::Start()
{
	SkillSetting();

	m_log = NewGO<SkillLog>(1,"sLog");
	m_log->SetText(skillName);

	return true;
}

void SkillBase::InitSkill(const wchar_t * name, float power, float time, float acc, int no)
{
	SetSkillName(name);
	SetSkillPower(power);
	SetCoolTime(time);
	SetAccuracy(acc);
	SetSkillNo(no);
}

int SkillBase::DamageCalcuration()
{
	//�_���[�W�v�Z���s���B
	int damage = 0;
	int Attack, Defence;

	//���@�U�����ǂ����B
	if (!IsMagic()) {
		Attack = m_user->GetStatusManager().GetStatus().ATK;
		Defence = m_target->GetStatusManager().GetStatus().DEF;
	}
	else {
		Attack = m_user->GetStatusManager().GetStatus().MAT;
		Defence = m_target->GetStatusManager().GetStatus().MDF;
	}
	
	//�_���[�W�v�Z���B
	damage = (int)((float)(Attack - Defence / 2) * skillPower);
	//0�������Ȃ��悤�ɂ���B
	damage = max(damage, 0);

	if (accuracy * 100 < rand() % 101){
		damage = 0;
	}

	return damage;
}

