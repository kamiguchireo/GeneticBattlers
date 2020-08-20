#include "stdafx.h"
#include "SkillBase.h"
#include "SkillLog.h"
#include "SkillDataLoad.h"

const float SkillBase::SKILL_SOUND_VOL = 0.6f;

SkillBase::SkillBase()
{
}


SkillBase::~SkillBase()
{
	if (m_user != nullptr && !m_user->IsDead()) {
		//�ҋ@��Ԃ̃A�j���[�V�����̍Đ��B
		m_user->AnimationIdle();
	}
	if (m_sound!=nullptr&&!m_sound->IsPlaying())
	{
		DeleteGO(m_sound);
	}

	//DeleteGO(m_log);
}

bool SkillBase::Start()
{

	m_log = NewGO<SkillLog>(4,"sLog");
	m_log->SetText(skillName);
	if (!m_calculator.IsAvailableSkill(m_user->GetStatusManager(),m_skillNo))
	{
		//MP������Ă��Ȃ�
		m_log->SetMPShortage(true);
		DeleteGO(this);
		m_isPlay = false;
	}
	else
	{
		//MP������Ă���B
		SkillSetting();
		m_isPlay = true;
	}

	return true;
}

void SkillBase::InitSkill(const wchar_t * name, float power, float time, float hitRate, int no)
{
	SetSkillName(name);
	//SetSkillPower(power);
	//SetCoolTime(time);
	//SetAccuracy(hitRate);
	SetSkillNo(no);
}

void SkillBase::InitSkill(SkillData data)
{
	SetSkillName(data.Name.c_str());
	if (data.targetNum == SkillDataLoad::MAX_TARGETS_MEMBER)
	{
		SetIsWide(true);
	}
	SetStatusChange(data.StatusChange);
	SetSkillNo(data.SkillNo);
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

void SkillBase::PlaySkill()
{
	if (!m_isWide)
	{
		m_skillEffect = NewGO<prefab::CEffect>(0);
		m_skillEffect->Play(m_playSkillPaths.m_effectPaths[m_playEffectNum]);
		CVector3 efPos = CreateEffectPosition(m_playSkillPaths.m_effectPosFlag[m_playEffectNum]);
		m_skillEffect->SetPosition(efPos);
		CQuaternion effectRot = CreateEffectRotation(m_playSkillPaths.m_effectPosFlag[m_playEffectNum]);
		m_skillEffect->SetRotation(effectRot);
	}
	else
	{
		auto list = m_target->GetTeamMenber();

		for (int i = 0; i < list.size(); i++)
		{
			//�����o�[�S�Ă��^�[�Q�b�g����B
			m_target = list[i];
			if (!m_target->IsDeath())
			{
				m_skillEffect = NewGO<prefab::CEffect>(0);
				m_skillEffect->Play(m_playSkillPaths.m_effectPaths[m_playEffectNum]);
				CVector3 efPos = CreateEffectPosition(m_playSkillPaths.m_effectPosFlag[m_playEffectNum]);
				m_skillEffect->SetPosition(efPos);
				CQuaternion effectRot = CreateEffectRotation(m_playSkillPaths.m_effectPosFlag[m_playEffectNum]);
				m_skillEffect->SetRotation(effectRot);
			}
		}
	}
	if (m_playSkillPaths.m_soundPaths[m_playEffectNum] != nullptr)
	{
		wchar_t path[256];
		wcscpy(path,m_playSkillPaths.m_soundPaths[m_playEffectNum]);
		m_sound = NewGO<prefab::CSoundSource>(0);
		m_sound->Init(path);
		m_sound->SetVolume(SKILL_SOUND_VOL);
		m_sound->Play(false);
	}

	m_playEffectNum++;
}

