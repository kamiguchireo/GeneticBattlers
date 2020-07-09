#include "stdafx.h"
#include "SkillHeal.h"

void SkillHeal::SkillSetting()
{
	//エフェクトの再生。
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	skillEffect->SetPosition(m_user->GetPosition() + CVector3::AxisY()*20.0f);
	skillEffect->SetScale(CVector3::One() * 50.0f);

	//アニメーションの再生。
	//m_user->AnimationMagic();
}

void SkillHeal::Update()
{
	if (m_healEffect == nullptr
		&& !skillEffect->IsPlay()) {
		//エフェクトの再生。
		m_healEffect = NewGO<prefab::CEffect>(0);
		m_healEffect->Play(effectPath);
		m_healEffect->SetPosition(m_target->GetPosition() + CVector3::AxisY()*20.0f);
		m_healEffect->SetScale(CVector3::One()*80.0f);
	}
	else if (m_healEffect != nullptr
		&& !m_healEffect->IsPlay()) {
		//回復量の計算。
		int result = m_user->GetStatusManager().GetStatus().MAT * skillPower;
		int res = m_target->Healing(result);

		//効果値を記録。
		m_user->SetDamageResult(res);
		//クールタイムの設定。
		m_user->SetCoolTime(coolTime);

		m_healEffect = nullptr;
		DeleteGO(this);
	}
}
