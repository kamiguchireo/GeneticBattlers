#include "stdafx.h"
#include "SkillHeal.h"

void SkillHeal::SkillSetting()
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

void SkillHeal::Update()
{
	if (m_target->IsDead()) {
		m_target = nullptr;
		m_user = nullptr;
		DeleteGO(this);
		return;
	}
	//if (m_healEffect == nullptr
	//	&& !skillEffect->IsPlay()) {
	//	//エフェクトの再生。
	//	m_healEffect = NewGO<prefab::CEffect>(0);
	//	m_healEffect->Play(effectPath);
	//	m_healEffect->SetPosition(m_target->GetPosition() + CVector3::AxisY()*20.0f);
	//	m_healEffect->SetScale(CVector3::One()*80.0f);
	//}
	//else if (m_healEffect != nullptr
	//	&& !m_healEffect->IsPlay()) {
	//	//回復量の計算。
	//	int result = m_user->GetStatusManager().GetStatus().MAT * skillPower;
	//	int res = m_target->Healing(result);

	//	//効果値を記録。
	//	m_user->SetDamageResult(res);
	//	//クールタイムの設定。
	//	m_user->SetCoolTime(coolTime);

	//	m_healEffect = nullptr;
	//	DeleteGO(this);
	//}
	if (!skillEffect->IsPlay())
	{
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
