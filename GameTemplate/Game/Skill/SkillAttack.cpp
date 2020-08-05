#include "stdafx.h"
#include "SkillAttack.h"

void SkillAttack::SkillSetting()
{
	//エフェクトの再生。
	PlaySkill();

	//アニメーションの再生。
	m_user->AnimationAttack();
}

void SkillAttack::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		m_isPlay = false;
		DeleteGO(this);
		return;
	}
	if (!skillEffect->IsPlay()) {
		if (m_playSkillPaths.m_effectPaths.size() > m_playEffectNum)
		{
			PlaySkill();
		}
		else
		{
			//ダメージを与える。
			int damage = DamageCalcuration();
			int res = m_target->Damage(damage);

			//効果値を記録。
			m_user->SetDamageResult(res);
			//クールタイムの設定。
			m_user->SetCoolTime(coolTime);

			m_isPlay = false;
			skillEffect = nullptr;
			DeleteGO(this);
		}
	}
}
