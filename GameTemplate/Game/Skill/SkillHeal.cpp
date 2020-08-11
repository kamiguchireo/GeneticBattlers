#include "stdafx.h"
#include "SkillHeal.h"

void SkillHeal::SkillSetting()
{
	//エフェクトの再生。
	PlaySkill();

	//アニメーションの再生。
	m_user->AnimationMagic();
}

void SkillHeal::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		m_isPlay = false;
		DeleteGO(this);
		return;
	}

	if (!m_skillEffect->IsPlay())
	{
		if (m_playSkillPaths.m_effectPaths.size() > m_playEffectNum)
		{
			PlaySkill();
		}
		else
		{
			int res = 0;
			if (!m_isWide)
			{
				//回復。
				res = m_calculator.SkillCalculation(m_user->GetStatusManager(), m_target->GetStatusManager(), m_skillNo);
			}
			else
			{
				res = WideHeal();
			}
			//効果値を記録。
			m_user->SetDamageResult(res);
			////クールタイムの設定。
			//m_user->SetCoolTime(coolTime);

			m_isPlay = false;
			m_skillEffect = nullptr;
			m_sound = nullptr;
			DeleteGO(this);
		}
	}
}

int SkillHeal::WideHeal()
{
	//チームメンバーを取得。
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//回復。
		res = m_calculator.SkillCalculation(m_user->GetStatusManager(), list[i]->GetStatusManager(), m_skillNo);
	}
	res /= static_cast<int>(list.size());		//平均をとる。

	return res;
}
