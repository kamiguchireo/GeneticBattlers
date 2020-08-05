#include "stdafx.h"
#include "SkillBase.h"
#include "SkillLog.h"
#include "SkillDataLoad.h"

SkillBase::SkillBase()
{
}


SkillBase::~SkillBase()
{
	if (m_user != nullptr && !m_user->IsDead()) {
		//�ҋ@��Ԃ̃A�j���[�V�����̍Đ��B
		m_user->AnimationIdle();
	}
	//DeleteGO(m_log);
}

bool SkillBase::Start()
{
	SkillSetting();

	m_log = NewGO<SkillLog>(4,"sLog");
	m_log->SetText(skillName);

	m_isPlay = true;

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

	if (accuracy * 100 < g_random.GetRandomInt() % 101){
		damage = 0;
	}

	return damage;
}


const CVector3 SkillBase::CreateEffectPosition(int enPos) const
{
	CVector3 effectPos = CVector3::Zero();
	switch (enPos)
	{
	case en_PosUser:
		//�g�p�҂̏�����B
		effectPos = m_user->GetPosition() + CVector3::AxisY() * 20.0f;
		break;

	case en_PosTarget:
		//�^�[�Q�b�g�̏�����B
		effectPos = m_target->GetPosition() + CVector3::AxisY() * 20.0f;
		break;
	default:
		break;
	}

	return effectPos;
}
const CQuaternion SkillBase::CreateEffectRotation(int enRot) const
{
	CQuaternion effectRot = CQuaternion::Identity();
	switch (enRot)
	{
	case en_PosUser:
		//�g�p�҂̏�����B
		effectRot = m_user->GetRotation();
		break;

	case en_PosTarget:
		//�^�[�Q�b�g�̏�����B
		effectRot = m_target->GetRotation();
		break;
	default:
		break;
	}
	return effectRot;
}

