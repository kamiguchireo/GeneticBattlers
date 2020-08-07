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
		//待機状態のアニメーションの再生。
		m_user->AnimationIdle();
	}
	if (m_sound!=nullptr)
	{
		DeleteGO(m_sound);
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
const CQuaternion SkillBase::CreateEffectRotation(int enRot) const
{
	CQuaternion effectRot = CQuaternion::Identity();
	switch (enRot)
	{
	case en_PosUser:
		//使用者の少し上。
		effectRot = m_user->GetRotation();
		break;

	case en_PosTarget:
		//ターゲットの少し上。
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
			//メンバー全てをターゲットする。
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

