#include "stdafx.h"
#include "SkillAttack.h"

void SkillAttack::SkillSetting()
{
	//エフェクトの再生。
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(m_effectPaths[m_playEffectNum]);
	CVector3 effectPos = GetEffectPos(en_PosUser);
	skillEffect->SetPosition(effectPos);
	skillEffect->SetRotation(m_user->GetRotation());
	//skillEffect->SetScale(CVector3::One() * 20.0f);

	m_playEffectNum++;

	//アニメーションの再生。
	m_user->AnimationAttack();
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
