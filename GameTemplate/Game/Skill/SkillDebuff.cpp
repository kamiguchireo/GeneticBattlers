#include "stdafx.h"
#include "SkillDebuff.h"

void SkillDebuff::SkillSetting()
{
	//エフェクトの再生。
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	CVector3 effectPos = CreateEffectPosition(en_PosUser);
	skillEffect->SetPosition(effectPos);

	//アニメーションの再生。
	m_user->AnimationMagic();
}

void SkillDebuff::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		DeleteGO(this);
		return;
	}

	if (!skillEffect->IsPlay()) {
		if (m_effectPaths.size() > m_playEffectNum)
		{
			if (!m_isWide)
			{
				skillEffect = NewGO<prefab::CEffect>(0);
				skillEffect->Play(m_effectPaths[m_playEffectNum]);
				CVector3 efPos = CreateEffectPosition(m_effectPosFlag[m_playEffectNum]);
				skillEffect->SetPosition(efPos);
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
						skillEffect = NewGO<prefab::CEffect>(0);
						skillEffect->Play(m_effectPaths[m_playEffectNum]);
						CVector3 efPos = CreateEffectPosition(m_effectPosFlag[m_playEffectNum]);
						skillEffect->SetPosition(efPos);
					}
				}
			}

			m_playEffectNum++;
		}
		else
		{
			//効果値。
			int res = 0;
			//バフをかける。
			if (!m_isWide) {
				//効果時間を計算。
				//float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * 5.0f);
				res = m_target->MonsterBuffAndDebuff(m_status, skillPower, DEBUFF_TIME);
			}
			else {	//全体にかける。
				res = WideDebuff();
			}

			//効果値を記録。
			m_user->SetDamageResult(res);
			//クールタイムの設定。
			m_user->SetCoolTime(coolTime);

			skillEffect = nullptr;
			DeleteGO(this);
		}
	}
}

int SkillDebuff::WideDebuff()
{
	//チームメンバーを取得。
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//全体にバフをかける。
		res += list[i]->MonsterBuffAndDebuff(m_status, skillPower, DEBUFF_TIME);
	}
	res /= static_cast<int>(list.size());		//上昇値の平均をとる。

	return res;
}
