#include "stdafx.h"
#include "SkillHeal.h"

bool SkillHeal::Start()
{
	//エフェクトの再生。
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	skillEffect->SetPosition(m_user->GetPosition() + CVector3::AxisY()*20.0f);
	skillEffect->SetScale(CVector3::One() * 50.0f);

	return true;
}

void SkillHeal::Update()
{
	if (!skillEffect->IsPlay()
		&& m_healEffect == nullptr) {
		//エフェクトの再生。
		m_healEffect = NewGO<prefab::CEffect>(0);
		m_healEffect->Play(effectPath);
		m_healEffect->SetPosition(m_target->GetPosition() + CVector3::AxisY()*20.0f);
		m_healEffect->SetScale(CVector3::One()*80.0f);

		skillEffect = nullptr;
	}
	if (m_healEffect->IsPlay()) {
		//回復量の計算。
		int result = m_user->GetStatusManager().GetStatus().MAT * skillPower;
		int res = m_target->Healing(result);

		//効果値を記録。
		m_user->SetDamageResult(res);
		//クールタイムの設定。
		m_user->SetCoolTime(coolTime);

		m_healEffect = nullptr;
	}
}
