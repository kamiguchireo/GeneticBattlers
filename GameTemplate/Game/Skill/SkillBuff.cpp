#include "stdafx.h"
#include "SkillBuff.h"

const float BUFF_TIME = 100.0f;

void SkillBuff::SkillSetting()
{
	//エフェクトの再生。
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	CVector3 effectPos = CreateEffectPosition(en_PosUser);
	skillEffect->SetPosition(effectPos);
	//skillEffect->SetScale(CVector3::One() * 50.0f);

	//アニメーションの再生。
	m_user->AnimationMagic();
}

void SkillBuff::Update()
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
				res = static_cast<int>(m_target->Monster_Buff(m_status, skillPower, BUFF_TIME));
			}
			else {	//全体にかける。
				res = WideBuff();
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

int SkillBuff::WideBuff()
{
	//チームメンバーを取得。
	auto list = m_target->GetTeamMenber();

	//float result = static_cast<float>(m_user->GetStatusManager().GetStatus().MAT * 5.0f);
	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//全体にバフをかける。
		res += static_cast<int>(list[i]->Monster_Buff(m_status, skillPower, BUFF_TIME));
	}
	res /= static_cast<int>(list.size());		//上昇値の平均をとる。

	return res;
}
