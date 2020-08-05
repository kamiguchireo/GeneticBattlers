#include "stdafx.h"
#include "SkillBuff.h"

void SkillBuff::SkillSetting()
{
	//エフェクトの再生。
	PlaySkill();

	//アニメーションの再生。
	m_user->AnimationMagic();
}

void SkillBuff::Update()
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
			m_isPlay = false;
			//効果値。
			int res = 0;
			//バフをかける。
			if (!m_isWide) {
				//効果時間を計算。
				//float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * 5.0f);
				res = m_target->MonsterBuffAndDebuff(m_status, skillPower, BUFF_TIME);
			}
			else {	//全体にかける。
				res = WideBuff();
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

int SkillBuff::WideBuff()
{
	//チームメンバーを取得。
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//全体にバフをかける。
		res += list[i]->MonsterBuffAndDebuff(m_status, skillPower, BUFF_TIME);
	}
	res /= static_cast<int>(list.size());		//上昇値の平均をとる。

	return res;
}
