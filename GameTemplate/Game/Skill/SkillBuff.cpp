#include "stdafx.h"
#include "SkillBuff.h"

void SkillBuff::SkillSetting()
{
	//エフェクトの再生。
	skillEffect = NewGO<prefab::CEffect>(0);
	skillEffect->Play(L"Assets/effect/chant1.efk");
	skillEffect->SetPosition(m_user->GetPosition() + CVector3::AxisY()*20.0f);
	skillEffect->SetScale(CVector3::One() * 50.0f);

	//アニメーションの再生。
	//m_user->AnimationMagic();
}

void SkillBuff::Update()
{
	if (!skillEffect->IsPlay()) {
		//効果値。
		int res = 0;
		//バフをかける。
		if (!m_isWide) {
			//効果時間を計算。
			int result = m_user->GetStatusManager().GetStatus().MAT * 5.0f;
			res = m_target->Monster_Buff(m_status, skillPower, result);
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

int SkillBuff::WideBuff()
{
	//効果時間の計算。
	int result = m_user->GetStatusManager().GetStatus().MAT * 5.0f;
	//チームメンバーを取得。
	auto list = m_target->GetTeamMenber();

	int res = 0;
	for (int i = 0; i < list.size(); i++) {
		//全体にバフをかける。
		res += list[i]->Monster_Buff(m_status, skillPower, result);
	}
	res /= list.size();		//上昇値の平均をとる。

	return res;
}
