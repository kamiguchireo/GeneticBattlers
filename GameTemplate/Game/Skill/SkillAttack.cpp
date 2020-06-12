#include "stdafx.h"
#include "SkillAttack.h"

bool SkillAttack::Start()
{
	//エフェクトの再生。
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(effectPath);
	skillEffect->SetPosition(m_user->GetPosition() + CVector3::AxisY()*20.0f);
	skillEffect->SetRotation(m_user->GetRotation());
	skillEffect->SetScale(CVector3::One() * 20.0f);

	return true;
}

void SkillAttack::Update()
{
	if (!skillEffect->IsPlay()) {
		//ダメージを与える。
		int damage = DamageCalcuration();
		int res = m_target->Damage(damage);

		//効果値を記録。
		m_user->SetDamageResult(res);
		//クールタイムの設定。
		m_user->SetCoolTime(coolTime);

		skillEffect = nullptr;
		DeleteGO(this);
	}
}
