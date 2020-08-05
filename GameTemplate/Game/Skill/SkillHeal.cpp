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

	if (!skillEffect->IsPlay())
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
				//回復量の計算。
				int result = static_cast<int>(m_user->GetStatusManager().GetStatus().MAT * skillPower);
				res = m_target->Healing(result);

			}
			else
			{
				res = WideHeal();
			}
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

int SkillHeal::WideHeal()
{
	//回復量の計算
	float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * skillPower);
	//チームメンバーを取得。
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//全体にバフをかける。
		res += list[i]->Healing(static_cast<int>(result));
	}
	res /= static_cast<int>(list.size());		//上昇値の平均をとる。

	return res;
}
