#include "stdafx.h"
#include "SkillBase.h"
#include "SkillLog.h"
#include "SkillDataLoad.h"

SkillBase::SkillBase()
{
}


SkillBase::~SkillBase()
{
	//待機状態のアニメーションの再生。
	m_user->AnimationIdle();
}

bool SkillBase::Start()
{
	SkillSetting();

	m_log = NewGO<SkillLog>(1,"sLog");
	m_log->SetText(skillName);

	return true;
}

void SkillBase::InitSkill(const wchar_t * name, float power, float time, float hitRate, int no)
{
	SetSkillName(name);
	SetSkillPower(power);
	SetCoolTime(time);
	SetAccuracy(hitRate);
	SetSkillNo(no);
}

void SkillBase::InitSkill(SkillData data)
{
	SetSkillName(data.Name.c_str());
	SetSkillPower(data.Power);
	SetCoolTime(data.CoolTime);
	SetAccuracy(data.HitRate);
	SetSkillNo(data.SkillNo);
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

const CVector3 & SkillBase::GetEffectPos(int enPos) const
{
	CVector3 effectPos = CVector3::Zero();
	switch (enPos)
	{
	case en_PosUser:
		//使用者の少し上。
		effectPos = m_user->GetPosition() + CVector3::AxisY() * 20.0f;
		break;

	case en_PosTarget:
		//ターゲットの少し上。
		effectPos = m_target->GetPosition() + CVector3::AxisY() * 20.0f;
		break;
	default:
		break;
	}

	return effectPos;
}

