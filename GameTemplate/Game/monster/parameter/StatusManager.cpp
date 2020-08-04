#include "stdafx.h"
#include "StatusManager.h"
#include "StatusUI.h"

int StatusManager::Healing(int healing)
{
	int res = healing;
	m_status.HP += healing;
	//最大HPを超えた。
	if (m_status.HP > m_statusBase.HP) {
		int diff = m_status.HP - m_statusBase.HP;
		res -= diff;		//超えた分だけ引く。

		m_status.HP = min(m_status.HP, m_statusBase.HP);
	}

	return res;
}

int StatusManager::Monster_Buff(StatusBuff status, float pow, float time)
{
	int res = 0;
	//倍率から1を引いておく。
	pow -= 1.0f;

	//バフをかける。
	switch (status)
	{
	case en_buff_ATK:
		res = static_cast<int>(m_statusBase.ATK * pow);	//上昇値の計算。
		m_buffValues[status] = res;

		break;
	case en_buff_DEF:
		res = static_cast<int>(m_statusBase.DEF * pow);	//上昇値の計算。
		m_buffValues[status] = res;

		break;
	case en_buff_MAT:
		res = static_cast<int>(m_statusBase.MAT * pow);	//上昇値の計算。
		m_buffValues[status] = res;

		break;
	case en_buff_MDF:
		res = static_cast<int>(m_statusBase.MDF * pow);	//上昇値の計算。
		m_buffValues[status] = res;

		break;
	case en_buff_DEX:
		res = static_cast<int>(m_statusBase.DEX * pow);	//上昇値の計算。
		m_buffValues[status] = res;

		break;
	}
	//バフの効果時間を設定。
	m_buffTimeList[status] = time;
	//バフの効果を反映。
	SumBufAndDebuff(status);

	return res;
}

int StatusManager::Monster_Debuff(StatusBuff status, float pow, float time)
{
	int res = 0;
	//倍率から1を引いておく。
	pow -= 1.0f;

	//バフをかける。
	switch (status)
	{
	case en_buff_ATK:
		res = static_cast<int>(m_statusBase.ATK * pow);//低下値の計算。
		m_debuffValues[status] = res;

		break;
	case en_buff_DEF:
		res = static_cast<int>(m_statusBase.DEF * pow);//低下値の計算。
		m_debuffValues[status] = res;

		break;
	case en_buff_MAT:
		res = static_cast<int>(m_statusBase.MAT * pow);//低下値の計算。
		m_debuffValues[status] = res;

		break;
	case en_buff_MDF:
		res = static_cast<int>(m_statusBase.MDF * pow);//低下値の計算。
		m_debuffValues[status] = res;

		break;
	case en_buff_DEX:
		res = static_cast<int>(m_statusBase.DEX * pow);//低下値の計算。
		m_debuffValues[status] = res;

		break;
	}
	//デバフの効果時間を設定。
	m_debuffTimeList[status] = time;
	//デバフの効果を反映。
	SumBufAndDebuff(status);

	//効果値の絶対値を取る。
	res = abs(res);

	return res;
}

void StatusManager::SumBufAndDebuff(int status)
{
	//バフとデバフを反映したステータスを出す。
	switch (status)
	{
	case en_buff_ATK:
		m_status.ATK = m_statusBase.ATK + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_DEF:
		m_status.DEF = m_statusBase.DEF + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_MAT:
		m_status.MAT = m_statusBase.MAT + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_MDF:
		m_status.MDF = m_statusBase.MDF + m_buffValues[status] + m_debuffValues[status];
		break;
	case en_buff_DEX:
		m_status.DEX = m_statusBase.DEX + m_buffValues[status] + m_debuffValues[status];
		break;
	}
}

void StatusManager::ResetBuff(int i)
{
	//バフによる上昇値を0にする
	m_buffValues[i] = 0;
	//バフの効果時間を0にする。
	m_buffTimeList[i] = 0.0f;

	//ステータスを元のステータスに戻す。(デバフがあるならそれも反映)
	SumBufAndDebuff(i);
}

void StatusManager::ResetDebuff(int i)
{
	//デバフによる低下値を0にする
	m_debuffValues[i] = 0;
	//デバフの効果時間を0にする。
	m_debuffTimeList[i] = 0;

	//ステータスの低下を元に戻す。
	SumBufAndDebuff(i);
}

bool StatusManager::AddATB()
{
	const float addTime = g_gameTime.GetFrameDeltaTime() * 2.0f;
	//死亡時は処理を中断する。
	if (m_stateAI == en_state_Death) return false;

	m_activeTime += (float)m_status.DEX * addTime;
	for (int i = 0; i < en_buff_num; i++) {
		if (m_buffTimeList[i] == 0.0f) continue;

		m_buffTimeList[i] -= addTime;
		if (m_buffTimeList[i] < 0.0f) {
			ResetBuff(i);
		}
	}

	//アクティブタイムゲージ。
	float res = m_activeTime / m_coolTime;
	res = min(1.0f, res);
	m_UI->SetScaling(res);

	if (m_activeTime > m_coolTime) {
		return true;
	}
	return false;
}

void StatusManager::StateUpdate()
{
	//現在HP/最大HPの割合からステートを変化させる。
	float nowHP = (float)m_status.HP / (float)m_statusBase.HP;
	//ステートの変更。
	if (2.0f / 3.0f < nowHP) {
		m_stateAI = en_state_Good;
	}
	else if (1.0f / 3.0f < nowHP
		&& 2.0f / 3.0f >= nowHP) {
		m_stateAI = en_state_Usually;
	}
	else if (0 < m_status.HP
		&& 1.0f / 3.0f >= nowHP) {
		m_stateAI = en_state_Bad;
	}
	else if (m_status.HP == 0) {
		m_stateAI = en_state_Death;
		ClearATB();
		m_UI->SetScaling(0.0f);
	}
	//UIに反映。
	if (m_UI->IsDead()) { return; }	//死亡時は処理しない。
	//float res = m_activeTime / m_coolTime;
	//res = min(1.0f, res);
	//ui->SetScaling(res);
	m_UI->SetHPScaling(nowHP);
}
